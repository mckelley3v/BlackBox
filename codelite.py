import gyp.common
import os.path
import copy
import re

generator_default_variables = {
    'EXECUTABLE_PREFIX': '',
    'EXECUTABLE_SUFFIX': '',
    'STATIC_LIB_PREFIX': '',
    'SHARED_LIB_PREFIX': '',
    'STATIC_LIB_SUFFIX': '',
    'SHARED_LIB_SUFFIX': '',
    'INTERMEDIATE_DIR': '$(IntermediateDirectory)',
    'SHARED_INTERMEDIATE_DIR': '$(IntermediateDirectory)',
    'OS': '',
    'PRODUCT_DIR': '%(PRODUCT_DIR)s',
    'LIB_DIR': '%(LIB_DIR)s',
    'RULE_INPUT_ROOT': '%(RULE_INPUT_ROOT)s',
    'RULE_INPUT_DIRNAME': '%(RULE_INPUT_DIRNAME)s',
    'RULE_INPUT_EXT': '%(RULE_INPUT_EXT)s',
    'RULE_INPUT_NAME': '%(RULE_INPUT_NAME)s',
    'RULE_INPUT_PATH': '%(RULE_INPUT_PATH)s',
    'CONFIGURATION_NAME': '$(ConfigurationName)',
}

def writeln(out, indent, text):
    tab = '\t'
    tabs = tab * indent
    out.write(tabs + text + '\n')

def ExpandVars(template, value_dict):
    # relies on '%(RULE_INPUT_ROOT)s' pattern defined in default_variables
    # and python's string formatting to replace %(NAME)s with value_dict['NAME']
    return template % value_dict


def GetRootProductDir(params):
    options = params.get('options', {})
    generator_flags = params.get('generator_flags', {})

    option_top_level_dir = options.toplevel_dir
    generator_flag_product_dir = generator_flags.get('product_dir', '/build/bin')
    product_dir = os.path.normpath(os.path.join(option_top_level_dir, generator_flag_product_dir))
    return product_dir

def GetRootIntermediateDir(params):
    options = params.get('options', {})
    generator_flags = params.get('generator_flags', {})

    option_top_level_dir = options.toplevel_dir
    generator_flag_intermediate_dir = generator_flags.get('intermediate_dir', '/build/temp')
    intermediate_dir = os.path.normpath(os.path.join(option_top_level_dir, generator_flag_intermediate_dir))
    return intermediate_dir

def CalculateVariables(default_variables, params):
    # Calculate additional variables for use in the build (called by gyp).
    target_os = gyp.common.GetFlavor(params)
    default_variables['OS'] = target_os
    if target_os == 'win':
        default_variables['EXECUTABLE_SUFFIX'] = '.exe'
        default_variables['STATIC_LIB_SUFFIX'] = '.lib'
        default_variables['SHARED_LIB_SUFFIX'] = '.dll'
    else:
        default_variables['STATIC_LIB_PREFIX'] = 'lib'
        default_variables['STATIC_LIB_SUFFIX'] = '.a'
        default_variables['SHARED_LIB_PREFIX'] = 'lib'
        default_variables['SHARED_LIB_SUFFIX'] = '.so'

def GetOutputDirForBuildFile(build_file, options):
    output_dir = os.path.dirname(build_file)
    if options.generator_output:
        output_dir = os.path.join(options.generator_output, output_dir)
    return output_dir

def GenerateWorkspace(build_file, target_list, target_dicts, options):
    config_names = target_dicts[target_list[0]]['configurations'].keys()
    workspace_name = os.path.splitext(os.path.basename(build_file))[0]
    workspace_dir = GetOutputDirForBuildFile(build_file, options)
    workspace_path = os.path.join(workspace_dir, '%s%s.workspace' % (workspace_name, options.suffix))

    # Get projects in the workspace, and their dependents.
    project_targets = gyp.common.AllTargets(target_list,
                                            target_dicts,
                                            build_file)

    gyp.common.EnsureDirExists(workspace_path)
    with open(workspace_path, 'w') as out:
        writeln(out, 0, '<?xml version="1.0" encoding="UTF-8"?>')
        writeln(out, 0, '<CodeLite_Workspace Name="%s" Database="%s.tags">' % (workspace_name, workspace_name))
        for project_target in project_targets:
            build_file, project_name = gyp.common.ParseQualifiedTarget(project_target)[0:2]
            project_dir = GetOutputDirForBuildFile(build_file, options)
            project_reldir = gyp.common.RelativePath(project_dir, workspace_dir)
            project_path = os.path.join(project_reldir, '%s%s.project' % (project_name, options.suffix))
            writeln(out, 1, '<Project Name="%s" Path="%s"/>' % (project_name, project_path))
        writeln(out, 1, '<BuildMatrix>')
        for config_name in config_names:
            writeln(out, 2, '<WorkspaceConfiguration Name="%s" Selected="yes">' % config_name)
            for project_target in project_targets:
                build_file, project_name = gyp.common.ParseQualifiedTarget(project_target)[0:2]
                writeln(out, 3, '<Project Name="%s" ConfigName="%s"/>' % (project_name, config_name))
            writeln(out, 2, '</WorkspaceConfiguration>')
        writeln(out, 1, '</BuildMatrix>')
        writeln(out, 0, '</CodeLite_Workspace>')

def GetProjectOutputAffix(project_type, default_variables):
    if project_type == 'executable':
        return (default_variables['EXECUTABLE_PREFIX'],
                default_variables['EXECUTABLE_SUFFIX'])
    elif project_type == 'static_library':
        return (default_variables['STATIC_LIB_PREFIX'],
                default_variables['STATIC_LIB_SUFFIX'])
    elif project_type == 'shared_library':
        return (default_variables['SHARED_LIB_PREFIX'],
                default_variables['SHARED_LIB_SUFFIX'])
    elif project_type == 'none':
        return ('', '')
    else:
        raise gyp.common.GypError('Invalid project type specified: "%s"' % project_type)

def IsProjectTypeLib(project_type):
    if project_type == 'static_library':
        return True
    elif project_type == 'shared_library':
        return True
    else:
        return False

def GetCodeLiteProjectType(project_type, codelite_project_dict):
    if project_type == 'executable':
        return 'Executable'
    elif project_type == 'static_library':
        return 'Static Library'
    elif project_type == 'shared_library':
        return 'Dynamic Library'
    elif project_type == 'none':
        return 'None'
    else:
        raise gyp.common.GypError('Invalid project type specified: "%s"' % project_type)

def GetCodeLiteProjectInternalType(project_type, codelite_project_dict):
    if project_type == 'executable':
        executable_type = codelite_project_dict.get('executable_type', 'Console')
        if executable_type == 'Console':
            return 'Console'
        elif executable_type == 'GUI':
            return 'GUI'
        else:
            raise gyp.common.GypError('Invalid executable_type specified: "%s"' % executable_type)
    elif project_type == 'static_library':
        return 'Library'
    elif project_type == 'shared_library':
        return 'Library'
    elif project_type == 'none':
        return 'None'
    else:
        raise gyp.common.GypError('Invalid project_type specified: "%s"' % project_type)

def ResolveVirtualDirectory(virtual_dirs, source_dir):
    source_dir_components = re.split(r'[\\/]', source_dir)
    current_dirs = virtual_dirs
    for component in source_dir_components:
        current_dirs = current_dirs.setdefault(component, {})
    return current_dirs

def ResolveVirtualDirectories(project_sources):
    virtual_dirs = {}
    for source in project_sources:
        (source_dir, source_name) = os.path.split(source)
        virtual_dir = ResolveVirtualDirectory(virtual_dirs, source_dir)
        virtual_dir.setdefault('<files>', []).append(source)
    return virtual_dirs

def WriteCodeliteProjectVirtualDirectory(out, indent, root, vname, vdir):
    if vname:
        writeln(out, indent, '<VirtualDirectory Name="%s">' % vname)

    for (name, content) in vdir.iteritems():
        if name == '<files>':
            for source in content:
                writeln(out, indent + 1, '<File Name="%s"/>' % os.path.join(root, source))
        else:
            WriteCodeliteProjectVirtualDirectory(out, indent + 1, root, name, content)

    if vname:
        writeln(out, indent, '</VirtualDirectory>')

def WriteCodeliteProjectVirtualDirectories(out, indent, root, virtual_dirs):
    for vname, vdir in virtual_dirs.iteritems():
        WriteCodeliteProjectVirtualDirectory(out, indent, root, vname, vdir)

def GenerateProject(project_target, target_list, target_dicts, params, options, default_variables):
    project_dict = target_dicts[project_target]
    if project_dict['toolset'] != 'target':
        raise gyp.common.GypError('Multiple toolsets not supported in codelite build (target %s)' % qualified_target)

    build_file = gyp.common.BuildFile(project_target)
    (build_file_dir, build_file_name) = os.path.split(build_file)

    project_name = project_dict['target_name']
    project_filename = project_name + options.suffix + '.project'
    project_dir = GetOutputDirForBuildFile(build_file, options)
    project_path = os.path.join(project_dir, project_filename)
    project_lib_dirs = project_dict.get('library_dirs', [])
    project_libs = project_dict.get('libraries', [])

    generator_output_dir = os.path.join(options.toplevel_dir, options.generator_output)
    project_reldir = gyp.common.RelativePath(project_dir, generator_output_dir)
    project_product_dir = os.path.join(GetRootProductDir(params), '$(ConfigurationName)')
    project_product_reldir = gyp.common.RelativePath(project_product_dir, project_dir)
    project_intermediate_dir = os.path.join(GetRootIntermediateDir(params), '$(ConfigurationName)', project_reldir, project_name)
    project_intermediate_reldir = gyp.common.RelativePath(project_intermediate_dir, project_dir)

    project_type = project_dict.get('type', 'none')
    project_sources = project_dict.get('sources', [])
    (project_output_prefix, project_output_suffix) = GetProjectOutputAffix(project_type, default_variables)
    project_dependencies = project_dict.get('dependencies', [])
    project_rules = project_dict.get('rules', [])

    codelite_project_dict = project_dict.get('configurations', {}).get('codelite_settings', {})

    codelite_project_type = GetCodeLiteProjectType(project_type, codelite_project_dict)
    codelite_project_internal_type = GetCodeLiteProjectInternalType(project_type, codelite_project_dict)
    # 'WorkingDirectory' is defined relative to build_file_dir
    codelite_project_working_preldir = codelite_project_dict.get('WorkingDirectory', gyp.common.RelativePath(project_product_dir, build_file_dir))
    codelite_project_working_dir = os.path.normpath(os.path.join(build_file_dir, codelite_project_working_preldir))
    codelite_project_working_reldir = gyp.common.RelativePath(codelite_project_working_dir, project_dir)
    # command must be relative to working_dir, not project_dir
    codelite_project_output = '%s$(ProjectName)%s' % (project_output_prefix, project_output_suffix)
    codelite_project_command = os.path.join('.', gyp.common.RelativePath(project_product_dir, codelite_project_working_dir), codelite_project_output) if project_type == 'executable' else ''
    codelite_project_command_args = codelite_project_dict.get('CommandArguments', '')

    codelite_project_is_gui = 'yes' if codelite_project_internal_type == 'GUI' else 'no'

    build_file_relpath = gyp.common.RelativePath(build_file_dir, project_dir)

    codelite_project_compiler_dict = codelite_project_dict.get('Compiler', {})
    codelite_project_compiler_options = codelite_project_compiler_dict.get('Options', '')
    codelite_project_compiler_c_options = codelite_project_compiler_dict.get('C_Options', '')
    codelite_project_compiler_assembler = codelite_project_compiler_dict.get('Assembler', '')

    codelite_project_linker_dict = codelite_project_dict.get('Linker', {})
    codelite_project_linker_options = codelite_project_linker_dict.get('Options', '')

    codelite_project_resource_compiler_dict = codelite_project_dict.get('ResourceCompiler', {})
    codelite_project_resource_compiler_options = codelite_project_resource_compiler_dict.get('Options', '')

    codelite_project_virtual_dirs = ResolveVirtualDirectories(project_sources)

    codelite_custom_rules_header = ''
    codelite_custom_rules_commands = ''
    if project_rules:
        for rule in project_rules:
            rule_sources = rule.get('rule_sources', [])
            if rule_sources:
                for rule_source in rule_sources:
                    rule_source_path = os.path.normpath(os.path.join(build_file_dir, rule_source))
                    (rule_source_dir, rule_source_basename) = os.path.split(rule_source_path)
                    rule_source_reldir = gyp.common.RelativePath(rule_source_dir, project_dir)
                    rule_source_relpath = os.path.normpath(os.path.join(rule_source_reldir, rule_source_basename))
                    (rule_source_root, rule_source_ext) = os.path.splitext(rule_source_basename)
                    rule_source_dict = {
                        'PRODUCT_DIR': project_product_reldir,
                        'LIB_DIR': project_product_reldir,
                        'RULE_INPUT_PATH': rule_source_relpath,
                        'RULE_INPUT_NAME': rule_source_basename,
                        'RULE_INTPUT_DIRNAME': rule_source_reldir,
                        'RULE_INPUT_ROOT': rule_source_root,
                        'RULE_INPUT_EXT': rule_source_ext,
                    }

                    outputs = [ExpandVars(output, rule_source_dict) for output in rule['outputs']]
                    message = ExpandVars(rule.get('message'), rule_source_dict)
                    codelite_custom_rules_header += ' '.join(outputs)
                    codelite_custom_rules_commands += '%s: %s\n' % (' '.join(outputs), rule_source_relpath)
                    codelite_custom_rules_commands += '\t@echo %s\n' % message
                    for output in outputs:
                        codelite_custom_rules_commands += '\t@mkdir -p $$(dirname %s)\n' % output

                    codelite_custom_rules_commands += '\t@%s\n' % ExpandVars(' '.join(rule.get('action')), rule_source_dict)
                    # copied from gyp/generator/make.py to handle multiple outputs from single makefile target
                    # NOTE mkelley: uncertain of robustness, see http://www.gnu.org/software/automake/manual/html_node/Multiple-Outputs.html
                    if len(outputs) > 1:
                        codelite_custom_rules_commands += '%s: %s\n' % (' '.join(outputs[1:]), outputs[0])
                        codelite_custom_rules_commands += '%s: ;\n' % (' '.join(outputs[1:]))
                    codelite_custom_rules_commands += '\n'

    gyp.common.EnsureDirExists(project_path)
    with open(project_path, 'w') as out:
        writeln(out, 0, '<?xml version="1.0" encoding="UTF-8"?>')
        writeln(out, 0, '<CodeLite_Project Name="%s" InternalType="%s">' % (project_name, codelite_project_internal_type))
        writeln(out, 1, '<Plugins/>')
        writeln(out, 1, '<Description/>')
        WriteCodeliteProjectVirtualDirectories(out,
                                               1,
                                               build_file_relpath,
                                               codelite_project_virtual_dirs)
        if project_dependencies:
            writeln(out, 1, '<Dependencies>')
            for dependent in project_dependencies:
                dependent_name = gyp.common.ParseQualifiedTarget(dependent)[1]
                writeln(out, 2, '<Project Name="%s"/>' % dependent_name)
            writeln(out, 1, '</Dependencies>')
        else:
            writeln(out, 1, '<Dependencies/>')

        writeln(out, 1, '<Settings Type="%s">' % codelite_project_type)
        writeln(out, 2, '<GlobalSettings>')
        writeln(out, 3, '<Compiler Options="%s" C_Options="%s" Assembler="%s"/>' % (codelite_project_compiler_options,
                                                                                    codelite_project_compiler_c_options,
                                                                                    codelite_project_compiler_assembler))
        writeln(out, 3, '<Linker Options="%s"/>' % codelite_project_linker_options)
        writeln(out, 3, '<ResourceCompiler Options="%s"/>' % codelite_project_resource_compiler_options)
        writeln(out, 2, '</GlobalSettings>')

        for config_name, config_dict in project_dict['configurations'].iteritems():
            # compiler, linker, debugger, exe console/gui
            config_include_dirs = config_dict.get('include_dirs', [])
            config_defines = config_dict.get('defines', [])

            codelite_config_dict = config_dict.get('codelite_settings', {})
            codelite_config_compiler_type = codelite_config_dict.get('CompilerType', 'GNU g++')
            codelite_config_debugger_type = codelite_config_dict.get('DebuggerType', 'GNU gdb debugger')
            codelite_config_build_cmp_with_global_settings = codelite_config_dict.get('BuildCmpWithGlobalSettings', 'append')
            codelite_config_build_lnk_with_global_settings = codelite_config_dict.get('BuildLnkWithGlobalSettings', 'append')
            codelite_config_build_res_with_global_settings = codelite_config_dict.get('BuildResWithGlobalSettings', 'append')

            codelite_config_compiler_dict = codelite_config_dict.get('Compiler', {})
            codelite_config_compiler_options = codelite_config_compiler_dict.get('Options', '')
            codelite_config_compiler_c_options = codelite_config_compiler_dict.get('C_Options', '')
            codelite_config_compiler_assembler = codelite_config_compiler_dict.get('Assembler', '')
            codelite_config_compiler_required = codelite_config_compiler_dict.get('Required', 'yes')
            codelite_config_compiler_pre_compiled_header = codelite_config_compiler_dict.get('PreCompiledHeader', '')
            codelite_config_compiler_pch_in_command_line = codelite_config_compiler_dict.get('PCHInCommandLine', 'no')
            codelite_config_compiler_use_different_pch_flags = codelite_config_compiler_dict.get('UseDifferentPCHFlags', 'no')
            codelite_config_compiler_pch_flags = codelite_config_compiler_dict.get('PCHFlags', '')

            codelite_config_linker_dict = codelite_config_dict.get('Linker', {})
            codelite_config_linker_options = codelite_config_linker_dict.get('Options', '')
            codelite_config_linker_required = codelite_config_linker_dict.get('Required', 'yes')

            codelite_config_resource_compiler_dict = codelite_config_dict.get('ResourceCompiler', {})
            codelite_config_resource_compiler_options = codelite_config_resource_compiler_dict.get('Options', '')
            codelite_config_resource_compiler_required = codelite_config_resource_compiler_dict.get('Required', 'no')

            writeln(out, 2, '<Configuration Name="%s" '
                                           'CompilerType="%s" '
                                           'DebuggerType="%s" '
                                           'Type="%s" '
                                           'BuildCmpWithGlobalSettings="%s" '
                                           'BuildLnkWithGlobalSettings="%s" '
                                           'BuildResWithGlobalSettings="%s">' % (config_name,
                                                                                 codelite_config_compiler_type,
                                                                                 codelite_config_debugger_type,
                                                                                 codelite_project_type,
                                                                                 codelite_config_build_cmp_with_global_settings,
                                                                                 codelite_config_build_lnk_with_global_settings,
                                                                                 codelite_config_build_res_with_global_settings))
            # Compiler
            writeln(out, 3, '<Compiler Options="%s" '
                                      'C_Options="%s" '
                                      'Assembler="%s" '
                                      'Required="%s" '
                                      'PreCompiledHeader="%s" '
                                      'PCHInCommandLine="%s" '
                                      'UseDifferentPCHFlags="%s" '
                                      'PCHFlags="%s">' % (codelite_config_compiler_options,
                                                          codelite_config_compiler_c_options,
                                                          codelite_config_compiler_required,
                                                          codelite_config_compiler_assembler,
                                                          codelite_config_compiler_pre_compiled_header,
                                                          codelite_config_compiler_pch_in_command_line,
                                                          codelite_config_compiler_use_different_pch_flags,
                                                          codelite_config_compiler_pch_flags))
            for include_dir in config_include_dirs:
                # special case: treat path with special codelite specific variables as already relative
                include_reldir = ''
                if include_dir.startswith(('$(IntermediateDirectory)', '$(OutDir)')):
                    include_reldir = include_dir
                else:
                    include_reldir = os.path.normpath(os.path.join(build_file_relpath, include_dir))
                writeln(out, 4, '<IncludePath Value="%s"/>' % include_reldir)

            for define in config_defines:
                writeln(out, 4, '<Preprocessor Value="%s"/>' % define)

            writeln(out, 3, '</Compiler>')

            # Linker
            if project_type == 'executable':
                writeln(out, 3, '<Linker Options="%s" '
                                        'Required="%s">' % (codelite_config_linker_options,
                                                            codelite_config_linker_required))

                # this assumes that all the libraries are being placed side-by-side in the product dir\
                writeln(out, 4, '<LibraryPath Value="%s"/>' % project_product_reldir)
                for project_lib_dir in project_lib_dirs:
                    writeln(out, 4, '<LibraryPath Value="%s"/>' % project_lib_dir)

                for dependent in project_dependencies:
                    dependent_name = gyp.common.ParseQualifiedTarget(dependent)[1]
                    dependent_dict = target_dicts[dependent]
                    dependent_type = dependent_dict.get('type', 'none')
                    if IsProjectTypeLib(dependent_type):
                        writeln(out, 4, '<Library Value="%s"/>' % dependent_name)

                for project_lib in project_libs:
                    project_lib_name = project_lib
                    if project_lib_name.startswith('-l'):
                        project_lib_name = project_lib_name[2:]
                    writeln(out, 4, '<Library Value="%s"/>' % project_lib_name)

                writeln(out, 3, '</Linker>')
            else:
                writeln(out, 3, '<Linker Options="%s" '
                                        'Required="%s"/>' % (codelite_config_linker_options,
                                                             codelite_config_linker_required))

            # ResourceCompiler
            writeln(out, 3, '<ResourceCompiler Options="%s" '
                                              'Required="%s"/>' % (codelite_config_resource_compiler_options,
                                                                   codelite_config_resource_compiler_required))

            writeln(out, 3, '<General OutputFile="%s" '
                                     'IntermediateDirectory="%s" '
                                     'Command="%s" '
                                     'CommandArguments="%s" '
                                     'WorkingDirectory="%s" '
                                     'PauseExecWhenProcTerminates="yes" '
                                     'IsGUIProgram="%s" '
                                     'IsEnabled="yes"/> ' % (os.path.join(project_product_reldir, codelite_project_output),
                                                             project_intermediate_reldir,
                                                             codelite_project_command,
                                                             codelite_project_command_args,
                                                             codelite_project_working_reldir,
                                                             codelite_project_is_gui))

            if project_rules:
                writeln(out, 3, '<AdditionalRules>')
                writeln(out, 4, '<CustomPreBuild>%s' % codelite_custom_rules_header)
                out.write(codelite_custom_rules_commands)
                writeln(out, 4, '</CustomPreBuild>')
                writeln(out, 3, '</AdditionalRules>')

            writeln(out, 2, '</Configuration>')

        writeln(out, 1, '</Settings>')
        writeln(out, 0, '</CodeLite_Project>')

def GenerateOutput(target_list, target_dicts, data, params):

    default_variables = copy.copy(generator_default_variables)
    CalculateVariables(default_variables, params)

    # Generate .workspace and .project files.
    options = params.get('options', {})

    # Generate workspace files for all build files ending in .gyp
    for build_file in data:
        # Validate build_file extension
        if not build_file.endswith('.gyp'):
            continue

        # Create workspace
        GenerateWorkspace(build_file,
                          target_list,
                          target_dicts,
                          options)

    # Generate project files for all targets
    for target in target_list:
        # Create project
        GenerateProject(target,
                        target_list,
                        target_dicts,
                        params,
                        options,
                        default_variables)

def PerformBuild(data, configurations, params):
    pass