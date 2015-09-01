import json

class InputPortDefinition(object):
    def __init__(self, portName, typeName, isOptional, isMultiplex):
        self.PortName = portName
        self.TypeName = typeName
        self.IsOptional = isOptional
        self.IsMultiplex = isMultiplex

    @staticmethod
    def fromDict(portDict):
        portName = portDict.get("PortName")
        typeName = portDict.get("TypeName")
        isOptional = portDict.get("IsOptional", False)
        isMultiplex = portDict.get("IsMultiplex", False)
        if (isinstance(portName, basestring) and
            isinstance(typeName, basestring) and
            isinstance(isOptional, bool) and
            isinstance(isMultiplex, bool)):
            return InputPortDefinition(portName, typeName, isOptional, isMultiplex)

        # error
        return None

class OutputPortDefinition(object):
    def __init__(self, portName, typeName):
        self.PortName = portName
        self.TypeName = typeName

    @staticmethod
    def fromDict(portDict):
        portName = portDict.get("PortName")
        typeName = portDict.get("TypeName")
        if (isinstance(portName, basestring) and
            isinstance(typeName, basestring)):
            return OutputPortDefinition(portName, typeName)

        # error
        return None

class ComponentDefinition(object):
    def __init__(self, name, inputPorts, outputPorts, annotations):
        self.Name = name
        self.InputPorts = inputPorts
        self.OutputPorts = outputPorts
        self.Annotations = annotations

    @staticmethod
    def fromDict(compDict):
        name = compDict.get("Name")
        inputPorts = compDict.get("InputPorts")
        outputPorts = compDict.get("OutputPorts")
        annotations = compDict.get("Annotations", {})

        if (isinstance(name, basestring) and
            isinstance(inputPorts, list) and
            isinstance(outputPorts, list) and
            isinstance(annotations, dict)):

            inputPortsObjList = [InputPortDefinition.fromDict(portDict) for portDict in inputPorts]
            outputPortsObjList = [OutputPortDefinition.fromDict(portDict) for portDict in outputPorts]
            return ComponentDefinition(name, inputPortsObjList, outputPortsObjList, annotations)

        # error
        return None

    @staticmethod
    def fromJSON(jsonStr):
        return ComponentDefinition.fromDict(json.loads(jsonStr))

    @staticmethod
    def fromFile(fin):
        return ComponentDefinition.fromDict(json.load(fin))

class SystemComponentInstance(object):
    def __init__(self, definitionName, instanceName, instanceData):
        self.DefinitionName = definitionName
        self.InstanceName = instanceName
        self.InstanceData = instanceData

class SystemConnectionPort(object):
    def __init__(self, componentInstanceName, portName):
        self.ComponentInstanceName = componentInstanceName
        self.PortName = portName

    @staticmethod
    def fromDict(portDict):
        componentInstanceName = portDict.get("ComponentInstanceName")
        portName = portDict.get("PortName")

        if (isinstance(componentInstanceName, basestring) and
            isinstance(portName, basestring)):

            return SystemConnectionPort(componentInstanceName, portName)

        #error
        return None

class SystemConnection(object):
    def __init__(self, sourcePort, targetPort):
        self.SourcePort = sourcePort
        self.TargetPort = targetPort

    @staticmethod
    def fromDict(connDict):
        sourcePort = connDict.get("SourcePort")
        targetPort = connDict.get("TargetPort")

        if (isinstance(sourcePort, dict) and
            isinstance(targetPort, dict)):

            sourcePortObj = SystemConnectionPort.fromDict(sourcePort)
            targetPortObj = SystemConnectionPort.fromDict(targetPort)
            return SystemConnection(sourcePortObj, targetPortObj)

        return None

class SystemDefinition(ComponentDefinition):
    def __init__(self, name, inputPorts, outputPorts, annotations, componentInstances, systemConnections):
        super(ComponentDefinition, self).__init__(name, inputPorts, outputPorts, annotations)
        self.ComponentInstances = componentInstances
        self.SystemConnections = systemConnections

    @staticmethod
    def fromDict(sysDict):
        name = sysDict.get("Name")
        inputPorts = sysDict.get("InputPorts")
        outputPorts = sysDict.get("OutputPorts")
        annotations = sysDict.get("Annotations", {})
        componentInstances = sysDict.get("ComponentInstances")
        systemConnections = sysDict.get("SystemConnections")

        if (isinstance(name, basestring) and
            isinstance(inputPorts, list) and
            isinstance(outputPorts, list) and
            isinstance(annotations, dict) and
            isinstance(componentInstances, list) and
            isinstance(systemConnections, list)):

            inputPortsObjList = [InputPortDefinition.fromDict(portDict) for portDict in inputPorts]
            outputPortsObjList = [OutputPortDefinition.fromDict(portDict) for portDict in outputPorts]
            componentInstancesObjList = [SystemComponentInstance.fromDict(compDict) for compDict in componentInstances]
            systemConnectionObjList = [SystemConnection.fromDict(connDict) for connDict in systemConnections]

        # error
        return None
