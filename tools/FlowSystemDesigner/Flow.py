import json
import os.path

class InputPortDefinition(object):
    def __init__(self,
                 port_name,
                 type_name,
                 is_optional = False,
                 is_multiplex = False):

        self.port_name = port_name
        self.type_name = type_name
        self.is_optional = is_optional
        self.is_multiplex = is_multiplex

    @classmethod
    def from_dict(cls, port_dict):
        port_name = port_dict.get("PortName")
        type_name = port_dict.get("TypeName")
        is_optional = port_dict.get("IsOptional", False)
        is_multiplex = port_dict.get("IsMultiplex", False)

        if (isinstance(port_name, basestring) and
            isinstance(type_name, basestring) and
            isinstance(is_optional, bool) and
            isinstance(is_multiplex, bool)):

            return cls(port_name,
                       type_name,
                       is_optional,
                       is_multiplex)

        # error
        return None

    def as_dict(self):
        return {"PortName": self.port_name,
                "TypeName": self.type_name,
                "IsOptional": self.is_optional,
                "IsMultiplex": self.is_multiplex}

class OutputPortDefinition(object):
    def __init__(self,
                 port_name,
                 type_name):

        self.port_name = port_name
        self.type_name = type_name

    @classmethod
    def from_dict(cls, port_dict):
        port_name = port_dict.get("PortName")
        type_name = port_dict.get("TypeName")

        if (isinstance(port_name, basestring) and
            isinstance(type_name, basestring)):

            return cls(port_name,
                       type_name)

        # error
        return None

    def as_dict(self):
        return {"PortName": self.port_name,
                "TypeName": self.type_name}

class ComponentDefinition(object):
    def __init__(self,
                 name,
                 input_ports = [],
                 output_ports = [],
                 annotations = {}):

        self.name = name
        self.input_ports = input_ports
        self.output_ports = output_ports
        self.annotations = annotations

    @classmethod
    def from_dict(cls, comp_dict):
        name = comp_dict.get("Name")
        input_ports = comp_dict.get("InputPorts", [])
        output_ports = comp_dict.get("OutputPorts", [])
        annotations = comp_dict.get("Annotations", {})

        if (isinstance(name, basestring) and
            isinstance(input_ports, list) and
            isinstance(output_ports, list) and
            isinstance(annotations, dict)):

            input_ports = [InputPortDefinition.from_dict(port_dict) for port_dict in input_ports]
            output_ports = [OutputPortDefinition.from_dict(port_dict) for port_dict in output_ports]

            return cls(name,
                       input_ports,
                       output_ports,
                       annotations)

        # error
        return None

    @classmethod
    def from_json(cls, json_str):
        return cls.from_dict(json.loads(json_str))

    @classmethod
    def from_file(cls, fin):
        return cls.from_dict(json.load(fin))

    def as_dict(self):
        return {"Name": self.name,
                "InputPorts": [port.as_dict() for port in self.input_ports],
                "OutputPorts": [port.as_dict() for port in self.output_ports],
                "Annotations": self.annotations}

class ComponentDefinitionFile(ComponentDefinition):
    def __init__(self,
                 name,
                 input_ports = [],
                 output_ports = [],
                 annotations = {},
                 path = ""):

        super(ComponentDefinitionFile, self).__init__(name,
                                                      input_ports,
                                                      output_ports,
                                                      annotations)
        self.path = path;

    @classmethod
    def from_file(cls, fin):
        self = super(ComponentDefinitionFile, cls).from_file(fin)
        if self is not None:
            self.path = fin.name
            return self

        #error
        return None

    def as_dict(self):
        d = super(ComponentDefinitionFile, self).as_dict()
        d["Path"] = self.path
        return d

class SystemComponentInstance(object):
    def __init__(self,
                 definition_name,
                 instance_name,
                 instance_data = {}):

        self.definition_name = definition_name
        self.instance_name = instance_name
        self.instance_data = instance_data

    @classmethod
    def from_dict(cls, comp_dict):
        definition_name = comp_dict.get("DefinitionName")
        instance_name = comp_dict.get("InstanceName")
        instance_data = comp_dict.get("InstanceData", {})

        if (isinstance(definition_name, basestring) and
            isinstance(instance_name, basestring) and
            isinstance(instance_data, dict)):

            return cls(definition_name,
                       instance_name,
                       instance_data)

        #error
        return None

    def as_dict(self):
        return {"DefinitionName": self.definition_name,
                "InstanceName": self.instance_name,
                "InstanceData": self.instance_data}

class SystemConnectionPort(object):
    def __init__(self,
                 component_instance_name,
                 port_name):

        self.component_instance_name = component_instance_name
        self.port_name = port_name

    @classmethod
    def from_dict(cls, port_dict):
        component_instance_name = port_dict.get("ComponentInstanceName")
        port_name = port_dict.get("PortName")

        if (isinstance(component_instance_name, basestring) and
            isinstance(port_name, basestring)):

            return cls(component_instance_name,
                       port_name)

        #error
        return None

    def as_dict(self):
        return {"ComponentInstanceName": self.component_instance_name,
                "PortName": self.port_name}

class SystemConnection(object):
    def __init__(self,
                 source_port,
                 target_port):

        self.source_port = source_port
        self.target_port = target_port

    @classmethod
    def from_dict(cls, conn_dict):
        source_port = conn_dict.get("SourcePort")
        target_port = conn_dict.get("TargetPort")

        if (isinstance(source_port, dict) and
            isinstance(target_port, dict)):

            source_port = SystemConnectionPort.from_dict(source_port)
            target_port = SystemConnectionPort.from_dict(target_port)

            return cls(source_port,
                       target_port)

        return None

    def as_dict(self):
        return {"SourcePort": self.source_port.as_dict(),
                "TargetPort": self.target_port.as_dict()}

class SystemDefinition(ComponentDefinition):
    def __init__(self,
                 name,
                 input_ports = [],
                 output_ports = [],
                 annotations = {},
                 component_instances = [],
                 system_connections = []):

        super(SystemDefinition, self).__init__(name,
                                               input_ports,
                                               output_ports,
                                               annotations)
        self.component_instances = component_instances
        self.system_connections = system_connections

    @classmethod
    def from_dict(cls, sys_dict):
        self = super(SystemDefinition, cls).from_dict(sys_dict)
        if self is None:
            return None

        component_instances = sys_dict.get("ComponentInstances", [])
        system_connections = sys_dict.get("SystemConnections", [])

        if (isinstance(component_instances, list) and
            isinstance(system_connections, list)):

            self.component_instances = [SystemComponentInstance.from_dict(comp_dict) for comp_dict in component_instances]
            self.system_connections = [SystemConnection.from_dict(conn_dict) for conn_dict in system_connections]
            return self

        # error
        return None

    def as_dict(self):
        d = super(SystemDefinition, self).as_dict()
        d["ComponentInstances"] = [comp.as_dict() for comp in self.component_instances]
        d["SystemConnections"] = [conn.as_dict() for conn in self.system_connections]
        return d

class SystemDefinitionBuilder(SystemDefinition):
    def __init__(self,
                 name,
                 input_ports = [],
                 output_ports = [],
                 annotations = {},
                 component_instances = [],
                 system_connections = [],
                 component_definitions = {},
                 path = ""):

        super(SystemDefinitionBuilder, self).__init__(name,
                                                      input_ports,
                                                      output_ports,
                                                      annotations,
                                                      component_instances,
                                                      system_connections)
        self.component_definitions = component_definitions
        self.path = path

    @classmethod
    def from_new(cls, name):
        return cls.from_dict({"Name": name,
                             "InputPorts": [],
                             "OutputPorts": [],
                             "Annotations": {},
                             "ComponentInstances": [],
                             "SystemConnections": [],
                             "ComponentDefinitions": {}})

    @classmethod
    def from_file(cls, fin):
        proj_dict = json.load(fin)

        self = super(SystemDefinitionBuilder, cls).from_dict(proj_dict)
        if self is not None:
            self.path = fin.name
            component_definitions = proj_dict.get("ComponentDefinitions", {})

            if isinstance(component_definitions, dict):

                self.component_definitions = {comp.name : comp for comp in map(self.load_component_definition, component_definitions)}
                return self

        return None

    def as_dict(self):
        d = super(SystemDefinitionBuilder, self).as_dict()
        d["ComponentDefinitions"] = [os.path.relpath(comp.path, self.path) for comp in self.component_definitions.itervalues()]
        return d

    def save(self, fout):
        self.path = fout.name
        json.dump(self.as_dict(),
                  fout,
                  sort_keys = True,
                  indent = 4,
                  separators = (',', ': '))

    def load_component_definition(self, component_definition_path):
        if not os.path.isabs(component_definition_path):
            component_definition_path = os.path.join(self.path, component_definition_path)

        component_definition = None
        with open(component_definition_path, "r") as fin:
            component_definition = ComponentDefinitionFile.from_file(fin)

        if component_definition is not None:
            self.component_definitions[component_definition.name] = component_definition
            return component_definition

        return None
