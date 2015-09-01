import json

class InputPortDefinition(object):
    def __init__(self,
                 portName,
                 typeName,
                 isOptional = False,
                 isMultiplex = False):

        self.PortName = portName
        self.TypeName = typeName
        self.IsOptional = isOptional
        self.IsMultiplex = isMultiplex

    @classmethod
    def fromDict(cls, portDict):
        portName = portDict.get("PortName")
        typeName = portDict.get("TypeName")
        isOptional = portDict.get("IsOptional", False)
        isMultiplex = portDict.get("IsMultiplex", False)

        if (isinstance(portName, basestring) and
            isinstance(typeName, basestring) and
            isinstance(isOptional, bool) and
            isinstance(isMultiplex, bool)):

            return cls(portName, typeName, isOptional, isMultiplex)

        # error
        return None

class OutputPortDefinition(object):
    def __init__(self,
                 portName,
                 typeName):

        self.PortName = portName
        self.TypeName = typeName

    @classmethod
    def fromDict(cls, portDict):
        portName = portDict.get("PortName")
        typeName = portDict.get("TypeName")

        if (isinstance(portName, basestring) and
            isinstance(typeName, basestring)):

            return cls(portName, typeName)

        # error
        return None

class ComponentDefinition(object):
    def __init__(self,
                 name,
                 inputPorts = [],
                 outputPorts = [],
                 annotations = {}):

        self.Name = name
        self.InputPorts = inputPorts
        self.OutputPorts = outputPorts
        self.Annotations = annotations

    @classmethod
    def fromDict(cls, compDict):
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

            return cls(name, inputPortsObjList, outputPortsObjList, annotations)

        # error
        return None

    @classmethod
    def fromJSON(cls, jsonStr):
        return cls.fromDict(json.loads(jsonStr))

    @classmethod
    def fromFile(cls, fin):
        return cls.fromDict(json.load(fin))

class SystemComponentInstance(object):
    def __init__(self,
                 definitionName,
                 instanceName,
                 instanceData = {}):

        self.DefinitionName = definitionName
        self.InstanceName = instanceName
        self.InstanceData = instanceData

class SystemConnectionPort(object):
    def __init__(self,
                 componentInstanceName,
                 portName):

        self.ComponentInstanceName = componentInstanceName
        self.PortName = portName

    @classmethod
    def fromDict(cls, portDict):
        componentInstanceName = portDict.get("ComponentInstanceName")
        portName = portDict.get("PortName")

        if (isinstance(componentInstanceName, basestring) and
            isinstance(portName, basestring)):

            return cls(componentInstanceName, portName)

        #error
        return None

class SystemConnection(object):
    def __init__(self,
                 sourcePort,
                 targetPort):

        self.SourcePort = sourcePort
        self.TargetPort = targetPort

    @classmethod
    def fromDict(cls, connDict):
        sourcePort = connDict.get("SourcePort")
        targetPort = connDict.get("TargetPort")

        if (isinstance(sourcePort, dict) and
            isinstance(targetPort, dict)):

            sourcePortObj = SystemConnectionPort.fromDict(sourcePort)
            targetPortObj = SystemConnectionPort.fromDict(targetPort)

            return cls(sourcePortObj, targetPortObj)

        return None

class SystemDefinition(ComponentDefinition):
    def __init__(self,
                 name,
                 inputPorts = [],
                 outputPorts = [],
                 annotations = {},
                 componentInstances = [],
                 systemConnections = []):

        super(SystemDefinition, self).__init__(name,
                                               inputPorts,
                                               outputPorts,
                                               annotations)
        self.ComponentInstances = componentInstances
        self.SystemConnections = systemConnections

    @classmethod
    def fromDict(cls, sysDict):
        self = super(SystemDefinition, cls).fromDict(sysDict)
        if self is None:
            return None

        componentInstances = sysDict.get("ComponentInstances")
        systemConnections = sysDict.get("SystemConnections")

        if (isinstance(componentInstances, list) and
            isinstance(systemConnections, list)):

            componentInstancesObjList = [SystemComponentInstance.fromDict(compDict) for compDict in componentInstances]
            systemConnectionObjList = [SystemConnection.fromDict(connDict) for connDict in systemConnections]

            self.ComponentInstances = componentInstancesObjList
            self.SystemConnections = systemConnectionObjList
            return self

        # error
        return None

class SystemDefinitionDesigner(SystemDefinition):
    def __init__(self,
                 name,
                 inputPorts = [],
                 outputPorts = [],
                 annotations = {},
                 componentInstances = [],
                 systemConnections = [],
                 componentDefinitions = {}):

        super(SystemDefinitionDesigner, self).__init__(name,
                                                       inputPorts,
                                                       outputPorts,
                                                       annotations,
                                                       componentInstances,
                                                       systemConnections)
        self.ComponentDefinitions = componentDefinitions

    @classmethod
    def fromDict(cls, projDict):
        self = super(SystemDefinitionDesigner, cls).fromDict(projDict)
        if self is None:
            return None

        componentDefinitions = projDict.get("ComponentDefinitions", {})

        if isinstance(componentDefinitions, dict):

            componentDefinitionsObjDict = {compDef.Name : compDef for compDef in map(ComponentDefinition.fromDict, componentDefinitions)}

            self.ComponentDefinitions = componentDefinitionsObjDict
            return self

        return None

    @classmethod
    def fromNew(cls, name):
        return cls.fromDict({"Name": name,
                             "InputPorts": [],
                             "OutputPorts": [],
                             "Annotations": {},
                             "ComponentInstances": [],
                             "SystemConnections": [],
                             "ComponentDefinitions": {}})

    @classmethod
    def fromJSON(cls, jsonStr):
        return cls.fromDict(json.loads(jsonStr))

    @classmethod
    def fromFile(cls, fin):
        return cls.fromDict(json.load(fin))

    def loadComponentDefinition(self, componentDefinitionPath):
        componentDefinition = None
        with open(componentDefinitionPath, "r") as componentDefinitionFile:
            componentDefinition = ComponentDefinition.fromFile(componentDefinitionFile)

        if not componentDefinition is None:
            # componentDefinition.Path = componentDefinitionPath
            self.ComponentDefinitions[componentDefinition.Name] = componentDefinition

            return componentDefinition

        return None