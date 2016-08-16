#!/usr/bin/python

from __future__ import print_function
from collections import OrderedDict
import xml.etree.ElementTree
import argparse
import re
import sys
import json

# =============================================================================

class Language_C89(object):
    def __init__(self):
        self.TypeMacroDict = {
            "apientry": "GL_API_ENTRY"
        }

        self.CodeDict = {
            "comment": [],
            "types": OrderedDict(),
            "enums": {},
            "enum_values": {},
        }

        types_dict = self.CodeDict["types"]

        types_dict["GL_API"] = {
            "name": "GL_API",
            "code":
"""
#ifndef GL_API_ENTRY
#   if defined(_WIN32) && !defined(__CYGWIN__)
#       define GL_API_ENTRY __stdcall
#   else
#       define GL_API_ENTRY
#   endif
#endif
""",
            "requires": None,
            "required": True,
        }

    def BuildCode_Comment(self, xml_elem):
        assert xml_elem.tag == "comment"
        return "/*\n%s\n*/" % (xml_elem.text or "")

    def BuildCode_Typedef(self, xml_elem):
        assert xml_elem.tag == "type"

        # accumulate all child elements as code
        # gl xml registry is already psuedo C

        code_str = xml_elem.text or ""
        for xml_child in list(xml_elem):
            code_str += self.TypeMacroDict.get(xml_child.tag, "")
            if xml_child.tag == "name":
                code_str += "%(name)s"
            elif xml_child.text:
                code_str += xml_child.text
            if xml_child.tail:
                code_str += xml_child.tail

        xml_attrib_comment = xml_elem.attrib.get("comment", None)
        if not xml_attrib_comment is None:
            code_str += " /* %s */" % xml_attrib_comment

        return code_str

    #def BuildCode_EnumGroup(self, xml_elem, group_dict):
    #    code_strs = []
    #    code_strs.append("enum %s" % group_dict["name"])
    #    code_strs.append("{")
    #    for enum in group_dict["enums"]:
    #        code_strs.append("\t%s = %(value)," % enum)
    #    code_strs.append("}")

    def ExportCode(self, api_dict, fout):
        include_guard = "%s_%s_%s%s" % (api_dict["api"].upper(),
                                        api_dict["version_major"],
                                        api_dict["version_minor"],
                                        "_CORE" if api_dict["profile"] == "core" else "")

        print("#ifndef %s" % include_guard, file = fout)
        print("#define %s" % include_guard, file = fout)

        for comment in self.CodeDict["comment"]:
            print(comment, file = fout)

        for type_entry in self.CodeDict["types"].itervalues():
            #if type_entry["required"]:
            print(type_entry["code"] % type_entry, file = fout)

        print("#endif /* %s */\n" % include_guard, file = fout)

# =============================================================================

class Language_C99(Language_C89):
    def __init__(self):
        super(Language_C99, self).__init__()
        # example of language-specific type override
        self.CodeDict["types"]["inttypes"] = {
            "name": "inttypes",
            "code": "#include <stdint.h>",
            "requires": None,
            "required": False,
        }

# =============================================================================

class Language_Cpp98(Language_C89):
    def __init__(self):
        super(Language_Cpp98, self).__init__()

# =============================================================================

class Language_Cpp11(Language_Cpp98):
    def __init__(self):
        super(Language_Cpp11, self).__init__()

        # example of language-specific type override
        self.CodeDict["types"]["inttypes"] = {
            "name": "inttypes",
            "code": "#include <stdint.h>",
            "requires": None,
            "required": False,
        }

# =============================================================================

def SetRequiredType(type_name, types_dict):
    type_dict = types_dict[type_name]
    if not type_dict["required"]:
        type_dict["required"] = True
        requires = type_dict["requires"]
        if not requires is None:
            SetRequiredType(requires, types_dict)

# =============================================================================

def ParseDict(xml_elem, tag_dict, *args):
    for xml_child in list(xml_elem):
        codegen_func = tag_dict.get(xml_child.tag, None)
        if not codegen_func is None:
            codegen_func(xml_child, *args)
        else:
            print("Unknown xml tag: \"%s\"" % xml_child.tag)

# =============================================================================

def ParseIgnored(xml_elem, tag_dict, *args):
    pass

# =============================================================================

def ParseComment(xml_elem, api_dict, language):
    comments = language.CodeDict["comment"]
    comments.append(language.BuildCode_Comment(xml_elem))

# =============================================================================

def ParseType(xml_elem, api_dict,  language):
    types_dict = language.CodeDict["types"]

    xml_attrib_api = xml_elem.attrib.get("api", None)
    if not xml_attrib_api is None:
        if xml_attrib_api != api_dict["api"]:
            return

    type_name = xml_elem.attrib.get("name") or xml_elem.find("name").text
    code_str = language.BuildCode_Typedef(xml_elem)
    requires = xml_elem.attrib.get("requires")

    type_dict = {
        "name": type_name,
        "code": code_str,
        "requires": requires,
        "required": False,
    }

    if not xml_elem.attrib.get("name") is None:
        # don't override types with name attrib
        # if typedef is already in the dictionary, don't override it
        # some types may already be pre-loaded into the dictionary
        types_dict.setdefault(type_name, type_dict)
    else:
        # always override types without name attrib
        types_dict[type_name] = type_dict

# =============================================================================

def ParseTypes(xml_elem, api_dict, language):
    tag_dict = {
        "type": ParseType,
    }

    ParseDict(xml_elem, tag_dict, api_dict, language)

# =============================================================================

def ParseEnumEntry(xml_elem, api_dict, language, enum_name, enum_dict):
    enum_values_dict = language.CodeDict["enum_values"]

    name = xml_elem.attrib.get("name")

    enum_dict.setdefault("values", []).append(name)
    enum_value_dict = enum_values_dict.setdefault(name, {"name": name,
                                                         "code": None,
                                                         "requires": None,
                                                         "required": False})
    enum_value_dict.setdefault("enums", []).append(enum_name) # consider using set instead of array

# =============================================================================

def ParseEnum(xml_elem, api_dict, language):
    enums_dict = language.CodeDict["enums"]

    enum_name = xml_elem.attrib.get("name")

    tag_dict = {
        "enum": ParseEnumEntry,
    }

    enum_dict = enums_dict.setdefault(enum_name, {"name": enum_name,
                                                  "code": None,
                                                  "requires": None,
                                                  "required": False})

    ParseDict(xml_elem, tag_dict, api_dict, language, enum_name, enum_dict)

# =============================================================================

def ParseEnums(xml_elem, api_dict, language):
    tag_dict = {
        "group": ParseEnum,
    }

    ParseDict(xml_elem, tag_dict, api_dict, language)

# =============================================================================

def ParseEnumValue(xml_elem, api_dict, language):
    enum_values_dict = language.CodeDict["enum_values"]

    name = xml_elem.attrib.get("name")
    value = xml_elem.attrib.get("value")
    alias = xml_elem.attrib.get("alias", None)

    enum_value_dict = enum_values_dict.setdefault(name, {"name": name,
                                                         "code": None,
                                                         "requires": None,
                                                         "required": False})
    enum_value_dict.setdefault("value", value)
    if not alias is None:
        enum_value_dict.setdefault("aliases", []).append(alias) # consider using set instead of array

# =============================================================================

def ParseEnumValues(xml_elem, api_dict, language):
    enums_dict = language.CodeDict["enums"]

    # not currently parsing enums attribs -- unsure of usage
    # namespace, group, start, end, vendor, comment

    namespace = xml_elem.attrib.get("namespace", None)

    tag_dict = {
        "enum": ParseEnumValue,
        "unused": ParseIgnored,
    }

    ParseDict(xml_elem, tag_dict, api_dict, language)

# =============================================================================

def ParseCommands(xml_elem, api_dict, language):
    pass

# =============================================================================

def ParseFeature(xml_elem, api_dict, language):
    pass

# =============================================================================

def ParseExtensions(xml_elem, api_dict, language):
    pass

# =============================================================================

def CodeGen(xml_elem, api_dict, language, fout):
    tag_dict = {
        "comment":    ParseComment,
        "types":      ParseTypes,
        "groups":     ParseEnums,
        "enums":      ParseEnumValues,
        "commands":   ParseCommands,
        "feature":    ParseFeature,
        "extensions": ParseExtensions,
    }

    ParseDict(xml_elem, tag_dict, api_dict, language)
    language.ExportCode(api_dict, fout)
    print(json.dumps(language.CodeDict, indent = 4, sort_keys = True))

# =============================================================================

def ParseApiDict(str):
    str = str.lower()
    api_patterns = ["^(?P<api>gl)_(?P<version_major>[1-2])_(?P<version_minor>[0-9])$",                      # match gl_(1 or 2)_(0-9)
                    "^(?P<api>gl)_(?P<version_major>[3-9])_(?P<version_minor>[0-9])(_(?P<profile>core))?$", # match gl_(3-9)_(0-9) or gl_(3-9)_(0-9)_core
                    "^(?P<api>gles)_(?P<version_major>[1-9])_(?P<version_minor>[0-9])?$"]                   # match gles_(1-9)_(0-9)
    api_regexes = [re.compile(pattern) for pattern in api_patterns]

    for api_regex in api_regexes:
        api_match = api_regex.match(str)
        if not api_match is None:
            group_dict = api_match.groupdict()
            api_str = group_dict.get("api", None)
            version_major_str = int(group_dict.get("version_major", 0))
            version_minor_str = int(group_dict.get("version_minor", 0))
            profile_str = group_dict.get("profile", "compatibility")

            api_str = "gles1" if api_str == "gles" and version_major_str == 1 else \
                      "gles2" if api_str == "gles" and version_major_str > 1 else \
                      api_str

            api_dict = {
                "api":           api_str,
                "version_major": version_major_str,
                "version_minor": version_minor_str,
                "profile":       profile_str,
            }
            return api_dict

    raise argparse.ArgumentTypeError("\"%s\" does match required format" % str)

# =============================================================================

def main(argv):
    language_dict = {
        "C89":   Language_C89(),
        "C99":   Language_C99(),
        "C++98": Language_Cpp98(),
        "C++11": Language_Cpp11(),
    }

    language_names = language_dict.keys()

    parser = argparse.ArgumentParser(description = "Generate OpenGL API")
    parser.add_argument("--api",
                        type = ParseApiDict,
                        help = "Select OpenGL API version (e.g. gl_3_3_core, gles_2_0)")
    parser.add_argument("--language",
                        choices = language_names,
                        default = language_names[0],
                        help = "Select output language")
    parser.add_argument("--output",
                        "-o",
                        metavar = "PATH",
                        nargs = "?",
                        type = argparse.FileType("w"),
                        default = sys.stdout,
                        help = "Write output to PATH")
    parser.add_argument("input",
                        nargs = "?",
                        type = argparse.FileType("rb"),
                        default = sys.stdin,
                        help = "Path to GL registry xml")

    args = parser.parse_args(argv[1:])

    registry_tree = xml.etree.ElementTree.parse(args.input)

    CodeGen(registry_tree.getroot(),
            args.api,
            language_dict[args.language],
            args.output)

if __name__ == "__main__":
    sys.exit(main(sys.argv))
