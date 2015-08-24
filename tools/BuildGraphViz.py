#!/usr/bin/python

import sys
import json

# TODO - load these definitions from the file system
component_definitions = json.loads(
"""
[
    {
        "Name": "Constant<int>",
        "InputPorts": null,
        "OutputPorts":
        [
            {"PortName": "Value", "TypeName": "int"}
        ],
        "Annotations":
        {
            "Process": "Never"
        }
    },
    {
        "Name": "Add<int>",
        "InputPorts":
        [
            {"PortName": "Lhs", "TypeName": "int"},
            {"PortName": "Rhs", "TypeName": "int"}
        ],
        "OutputPorts":
        [
            {"PortName": "Result", "TypeName": "int"}
        ],
        "Annotations":
        {
            "Process": "Always"
        }
    }
]
"""
)

def BuildGraphVizSafeStr(str):
   str = str.replace(":", "")
   str = str.replace("<", "&lt;")
   str = str.replace(">", "&gt;")
   str = str.replace("\n", "\\n")
   return str
   
def BuildSystemInputDefinitionDict(definition):
   return \
      {
         "Name": definition["Name"],
         "InputPorts": None,
         "OutputPorts": definition["InputPorts"],
      }

def BuildSystemOutputDefinitionDict(definition):
   return \
      {
         "Name": definition["Name"],
         "InputPorts": definition["OutputPorts"],
         "OutputPorts": None,
      }

def BuildComponentGraphVizStr(instance, definition):
   input_ports = definition["InputPorts"]
   output_ports = definition["OutputPorts"]

   inputs_str = ""
   inputs_str_delim = ""
   if not input_ports is None:
      for input_port in input_ports:
         input_port_name = input_port["PortName"]
         input_port_type = input_port["TypeName"]
         inputs_str += "%s<%s>%s\\n%s" % (inputs_str_delim,
                                          input_port_name,
                                          input_port_type,
                                          input_port_name)
         inputs_str_delim = "|"

   outputs_str = ""
   outputs_str_delim = ""
   if not output_ports is None:
      for output_port in output_ports:
         output_port_name = output_port["PortName"]
         output_port_type = output_port["TypeName"]
         outputs_str += u"%s<%s>%s\\n%s" % (outputs_str_delim,
                                            output_port_name,
                                            output_port_type,
                                            output_port_name)
         outputs_str_delim = "|"

   instance_name_safe = BuildGraphVizSafeStr(instance["InstanceName"])
   instance_data = instance.get("InstanceData", "")
   if instance_data != "":
      instance_data = "%s\n%s" % (definition["Name"],
                                  instance_data)
   else:
      instance_data = definition["Name"]

   instance_data_safe = BuildGraphVizSafeStr(instance_data)
   return "\t%s [shape = record, label = \"<name>%s|{{%s}|{%s}|{%s}}\"]\n" % (instance_name_safe,
                                                                              instance_name_safe,
                                                                              inputs_str,
                                                                              instance_data_safe,
                                                                              outputs_str)

def BuildSystemGraphVizStr(file_name):
   result = ""
   file_text = ""
   with open(file_name, "r") as fin:
      file_text = fin.read()

   graph_dict = json.loads(file_text)
   component_definitions_dict = {}
   for component_definition in component_definitions:
      component_definitions_dict[component_definition["Name"]] = component_definition

   system_interface = graph_dict["Interface"]

   result += "digraph %s\n{\n\trankdir=LR\n" % system_interface["Name"]
   if not system_interface["InputPorts"] is None:
      result += BuildComponentGraphVizStr({"InstanceName": "in:"}, BuildSystemInputDefinitionDict(system_interface))
   if not system_interface["OutputPorts"] is None:
      result += BuildComponentGraphVizStr({"InstanceName": "out:"}, BuildSystemOutputDefinitionDict(system_interface))
   
   for instance in graph_dict["ComponentInstances"]:
      result += BuildComponentGraphVizStr(instance, component_definitions_dict[instance["DefinitionName"]])

   for connection in graph_dict["Connections"]:
      connection_source = connection["SourcePort"]
      connection_source_instance_name = connection_source["ComponentInstanceName"]
      connection_source_instance_name_safe = BuildGraphVizSafeStr(connection_source_instance_name)
      connection_source_port_name = connection_source["PortName"]
      connection_target = connection["TargetPort"]
      connection_target_instance_name = connection_target["ComponentInstanceName"]
      connection_target_instance_name_safe = BuildGraphVizSafeStr(connection_target_instance_name)
      connection_target_port_name = connection_target["PortName"]
      result += "\t\"%s\":%s -> \"%s\":%s;\n" % (connection_source_instance_name_safe,
                                                 connection_source_port_name,
                                                 connection_target_instance_name_safe,
                                                 connection_target_port_name)
   result += "}\n"
   return result


def main(argv):
   print BuildSystemGraphVizStr(argv[1])

if __name__ == "__main__":
   sys.exit(main(sys.argv))