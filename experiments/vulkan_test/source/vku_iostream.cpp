#include "vku_iostream.hpp"
#include <ostream>

// ====================================================================================================================
// Implementation
// ====================================================================================================================

int& vku::iostream::indent_level()
{
   static int s_IndentLevel = 0;
   return s_IndentLevel;
}

// ====================================================================================================================

std::ostream& vku::iostream::indent_push(std::ostream &out)
{
   ++indent_level();
   return out;
};

// ====================================================================================================================

std::ostream& vku::iostream::indent_pop(std::ostream &out)
{
   --indent_level();
   return out;
};

// ====================================================================================================================

std::ostream& vku::iostream::indent(std::ostream &out)
{
   int const n = indent_level();
   for(int i = 0; i < n; ++i)
   {
      out.put('\t');
   }

   return out;
}

// ====================================================================================================================

std::string vku::iostream::uuid_to_string(uint8_t const (&value)[VK_UUID_SIZE])
{
    static_assert(VK_UUID_SIZE == 16, "Unexpected VK_UUID_SIZE");

    std::size_t const uuid_buffer_size = 2 * VK_UUID_SIZE + 4 + 1; // 2 chars for each byte, 4 dashes, 1 null
    char uuid_buffer[uuid_buffer_size] = {};
    std::snprintf(uuid_buffer,
                  uuid_buffer_size,
                  "%02x%02x%02x%02x-"
                  "%02x%02x-"
                  "%02x%02x-"
                  "%02x%02x-"
                  "%02x%02x%02x%02x%02x%02x",
                  value[0], value[1], value[2], value[3],
                  value[4], value[5],
                  value[6], value[7],
                  value[8], value[9],
                  value[10], value[11], value[12], value[13], value[14], value[15]);

    return std::string(uuid_buffer);
}

// ====================================================================================================================

std::string vku::iostream::queue_flags_to_string(VkQueueFlags const &value)
{
    std::string result;

    if(value)
    {
        char const *prefix = "";
        if(value & VK_QUEUE_GRAPHICS_BIT)
        {
            result += prefix;
            result += "VK_QUEUE_GRAPHICS_BIT";
            prefix = " | ";
        }

        if(value & VK_QUEUE_COMPUTE_BIT)
        {
            result += prefix;
            result += "VK_QUEUE_COMPUTE_BIT";
            prefix = " | ";
        }

        if(value & VK_QUEUE_TRANSFER_BIT)
        {
            result += prefix;
            result += "VK_QUEUE_TRANSFER_BIT";
            prefix = " | ";
        }

        if(value & VK_QUEUE_SPARSE_BINDING_BIT)
        {
            result += prefix;
            result += "VK_QUEUE_SPARSE_BINDING_BIT";
            prefix = " | ";
        }
    }
    else
    {
        result = "0";
    }

    return result;
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkPhysicalDeviceProperties const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "apiVersion:        " << VK_VERSION_MAJOR(value.apiVersion)    << "." << VK_VERSION_MINOR(value.apiVersion)    << "." << VK_VERSION_PATCH(value.apiVersion)    << "\n";
    out << indent << "driverVersion:     " << VK_VERSION_MAJOR(value.driverVersion) << "." << VK_VERSION_MINOR(value.driverVersion) << "." << VK_VERSION_PATCH(value.driverVersion) << "\n";
    out << indent << "vendorID:          " << value.vendorID          << "\n";
    out << indent << "deviceID:          " << value.deviceID          << "\n";
    out << indent << "deviceType:        " << value.deviceType        << "\n";
    out << indent << "deviceName:        " << value.deviceName        << "\n";
    out << indent << "pipelineCacheUUID: " << uuid_to_string(value.pipelineCacheUUID) << "\n";
    out << indent << "limits:            " << value.limits            << "\n";
    out << indent << "sparseProperties:  " << value.sparseProperties  << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkPhysicalDeviceType const &value)
{
    switch(value)
    {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            return out << "VK_PHYSICAL_DEVICE_TYPE_OTHER";

        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            return out << "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU";

        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            return out << "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU";

        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            return out << "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU";

        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            return out << "VK_PHYSICAL_DEVICE_TYPE_CPU";

        default:
            return out;
    }
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkPhysicalDeviceLimits const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "maxImageDimension1D:                             " << value.maxImageDimension1D << "\n";
    out << indent << "maxImageDimension2D:                             " << value.maxImageDimension2D << "\n";
    out << indent << "maxImageDimension3D:                             " << value.maxImageDimension3D << "\n";
    out << indent << "maxImageDimensionCube:                           " << value.maxImageDimensionCube << "\n";
    out << indent << "maxImageArrayLayers:                             " << value.maxImageArrayLayers << "\n";
    out << indent << "maxTexelBufferElements:                          " << value.maxTexelBufferElements << "\n";
    out << indent << "maxUniformBufferRange:                           " << value.maxUniformBufferRange << "\n";
    out << indent << "maxStorageBufferRange:                           " << value.maxStorageBufferRange << "\n";
    out << indent << "maxPushConstantsSize:                            " << value.maxPushConstantsSize << "\n";
    out << indent << "maxMemoryAllocationCount:                        " << value.maxMemoryAllocationCount << "\n";
    out << indent << "maxSamplerAllocationCount:                       " << value.maxSamplerAllocationCount << "\n";
    out << indent << "bufferImageGranularity:                          " << value.bufferImageGranularity << "\n";
    out << indent << "sparseAddressSpaceSize:                          " << value.sparseAddressSpaceSize << "\n";
    out << indent << "maxBoundDescriptorSets:                          " << value.maxBoundDescriptorSets << "\n";
    out << indent << "maxPerStageDescriptorSamplers:                   " << value.maxPerStageDescriptorSamplers << "\n";
    out << indent << "maxPerStageDescriptorUniformBuffers:             " << value.maxPerStageDescriptorUniformBuffers << "\n";
    out << indent << "maxPerStageDescriptorStorageBuffers:             " << value.maxPerStageDescriptorStorageBuffers << "\n";
    out << indent << "maxPerStageDescriptorSampledImages:              " << value.maxPerStageDescriptorSampledImages << "\n";
    out << indent << "maxPerStageDescriptorStorageImages:              " << value.maxPerStageDescriptorStorageImages << "\n";
    out << indent << "maxPerStageDescriptorInputAttachments:           " << value.maxPerStageDescriptorInputAttachments << "\n";
    out << indent << "maxPerStageResources:                            " << value.maxPerStageResources << "\n";
    out << indent << "maxDescriptorSetSamplers:                        " << value.maxDescriptorSetSamplers << "\n";
    out << indent << "maxDescriptorSetUniformBuffers:                  " << value.maxDescriptorSetUniformBuffers << "\n";
    out << indent << "maxDescriptorSetUniformBuffersDynamic:           " << value.maxDescriptorSetUniformBuffersDynamic << "\n";
    out << indent << "maxDescriptorSetStorageBuffers:                  " << value.maxDescriptorSetStorageBuffers << "\n";
    out << indent << "maxDescriptorSetStorageBuffersDynamic:           " << value.maxDescriptorSetStorageBuffersDynamic << "\n";
    out << indent << "maxDescriptorSetSampledImages:                   " << value.maxDescriptorSetSampledImages << "\n";
    out << indent << "maxDescriptorSetStorageImages:                   " << value.maxDescriptorSetStorageImages << "\n";
    out << indent << "maxDescriptorSetInputAttachments:                " << value.maxDescriptorSetInputAttachments << "\n";
    out << indent << "maxVertexInputAttributes:                        " << value.maxVertexInputAttributes << "\n";
    out << indent << "maxVertexInputBindings:                          " << value.maxVertexInputBindings << "\n";
    out << indent << "maxVertexInputAttributeOffset:                   " << value.maxVertexInputAttributeOffset << "\n";
    out << indent << "maxVertexInputBindingStride:                     " << value.maxVertexInputBindingStride << "\n";
    out << indent << "maxVertexOutputComponents:                       " << value.maxVertexOutputComponents << "\n";
    out << indent << "maxTessellationGenerationLevel:                  " << value.maxTessellationGenerationLevel << "\n";
    out << indent << "maxTessellationPatchSize:                        " << value.maxTessellationPatchSize << "\n";
    out << indent << "maxTessellationControlPerVertexInputComponents:  " << value.maxTessellationControlPerVertexInputComponents << "\n";
    out << indent << "maxTessellationControlPerVertexOutputComponents: " << value.maxTessellationControlPerVertexOutputComponents << "\n";
    out << indent << "maxTessellationControlPerPatchOutputComponents:  " << value.maxTessellationControlPerPatchOutputComponents << "\n";
    out << indent << "maxTessellationControlTotalOutputComponents:     " << value.maxTessellationControlTotalOutputComponents << "\n";
    out << indent << "maxTessellationEvaluationInputComponents:        " << value.maxTessellationEvaluationInputComponents << "\n";
    out << indent << "maxTessellationEvaluationOutputComponents:       " << value.maxTessellationEvaluationOutputComponents << "\n";
    out << indent << "maxGeometryShaderInvocations:                    " << value.maxGeometryShaderInvocations << "\n";
    out << indent << "maxGeometryInputComponents:                      " << value.maxGeometryInputComponents << "\n";
    out << indent << "maxGeometryOutputComponents:                     " << value.maxGeometryOutputComponents << "\n";
    out << indent << "maxGeometryOutputVertices:                       " << value.maxGeometryOutputVertices << "\n";
    out << indent << "maxGeometryTotalOutputComponents:                " << value.maxGeometryTotalOutputComponents << "\n";
    out << indent << "maxFragmentInputComponents:                      " << value.maxFragmentInputComponents << "\n";
    out << indent << "maxFragmentOutputAttachments:                    " << value.maxFragmentOutputAttachments << "\n";
    out << indent << "maxFragmentDualSrcAttachments:                   " << value.maxFragmentDualSrcAttachments << "\n";
    out << indent << "maxFragmentCombinedOutputResources:              " << value.maxFragmentCombinedOutputResources << "\n";
    out << indent << "maxComputeSharedMemorySize:                      " << value.maxComputeSharedMemorySize << "\n";
    out << indent << "maxComputeWorkGroupCount:                        " << value.maxComputeWorkGroupCount << "\n";
    out << indent << "maxComputeWorkGroupInvocations:                  " << value.maxComputeWorkGroupInvocations << "\n";
    out << indent << "maxComputeWorkGroupSize:                         " << value.maxComputeWorkGroupSize << "\n";
    out << indent << "subPixelPrecisionBits:                           " << value.subPixelPrecisionBits << "\n";
    out << indent << "subTexelPrecisionBits:                           " << value.subTexelPrecisionBits << "\n";
    out << indent << "mipmapPrecisionBits:                             " << value.mipmapPrecisionBits << "\n";
    out << indent << "maxDrawIndexedIndexValue:                        " << value.maxDrawIndexedIndexValue << "\n";
    out << indent << "maxDrawIndirectCount:                            " << value.maxDrawIndirectCount << "\n";
    out << indent << "maxSamplerLodBias:                               " << value.maxSamplerLodBias << "\n";
    out << indent << "maxSamplerAnisotropy:                            " << value.maxSamplerAnisotropy << "\n";
    out << indent << "maxViewports:                                    " << value.maxViewports << "\n";
    out << indent << "maxViewportDimensions:                           " << value.maxViewportDimensions << "\n";
    out << indent << "viewportBoundsRange:                             " << value.viewportBoundsRange << "\n";
    out << indent << "viewportSubPixelBits:                            " << value.viewportSubPixelBits << "\n";
    out << indent << "minMemoryMapAlignment:                           " << value.minMemoryMapAlignment << "\n";
    out << indent << "minTexelBufferOffsetAlignment:                   " << value.minTexelBufferOffsetAlignment << "\n";
    out << indent << "minUniformBufferOffsetAlignment:                 " << value.minUniformBufferOffsetAlignment << "\n";
    out << indent << "minStorageBufferOffsetAlignment:                 " << value.minStorageBufferOffsetAlignment << "\n";
    out << indent << "minTexelOffset:                                  " << value.minTexelOffset << "\n";
    out << indent << "maxTexelOffset:                                  " << value.maxTexelOffset << "\n";
    out << indent << "minTexelGatherOffset:                            " << value.minTexelGatherOffset << "\n";
    out << indent << "maxTexelGatherOffset:                            " << value.maxTexelGatherOffset << "\n";
    out << indent << "minInterpolationOffset:                          " << value.minInterpolationOffset << "\n";
    out << indent << "maxInterpolationOffset:                          " << value.maxInterpolationOffset << "\n";
    out << indent << "subPixelInterpolationOffsetBits:                 " << value.subPixelInterpolationOffsetBits << "\n";
    out << indent << "maxFramebufferWidth:                             " << value.maxFramebufferWidth << "\n";
    out << indent << "maxFramebufferHeight:                            " << value.maxFramebufferHeight << "\n";
    out << indent << "maxFramebufferLayers:                            " << value.maxFramebufferLayers << "\n";
    out << indent << "framebufferColorSampleCounts:                    " << value.framebufferColorSampleCounts << "\n";
    out << indent << "framebufferDepthSampleCounts:                    " << value.framebufferDepthSampleCounts << "\n";
    out << indent << "framebufferStencilSampleCounts:                  " << value.framebufferStencilSampleCounts << "\n";
    out << indent << "framebufferNoAttachmentsSampleCounts:            " << value.framebufferNoAttachmentsSampleCounts << "\n";
    out << indent << "maxColorAttachments:                             " << value.maxColorAttachments << "\n";
    out << indent << "sampledImageColorSampleCounts:                   " << value.sampledImageColorSampleCounts << "\n";
    out << indent << "sampledImageIntegerSampleCounts:                 " << value.sampledImageIntegerSampleCounts << "\n";
    out << indent << "sampledImageDepthSampleCounts:                   " << value.sampledImageDepthSampleCounts << "\n";
    out << indent << "sampledImageStencilSampleCounts:                 " << value.sampledImageStencilSampleCounts << "\n";
    out << indent << "storageImageSampleCounts:                        " << value.storageImageSampleCounts << "\n";
    out << indent << "maxSampleMaskWords:                              " << value.maxSampleMaskWords << "\n";
    out << indent << "timestampComputeAndGraphics:                     " << value.timestampComputeAndGraphics << "\n";
    out << indent << "timestampPeriod:                                 " << value.timestampPeriod << "\n";
    out << indent << "maxClipDistances:                                " << value.maxClipDistances << "\n";
    out << indent << "maxCullDistances:                                " << value.maxCullDistances << "\n";
    out << indent << "maxCombinedClipAndCullDistances:                 " << value.maxCombinedClipAndCullDistances << "\n";
    out << indent << "discreteQueuePriorities:                         " << value.discreteQueuePriorities << "\n";
    out << indent << "pointSizeRange:                                  " << value.pointSizeRange << "\n";
    out << indent << "lineWidthRange:                                  " << value.lineWidthRange << "\n";
    out << indent << "pointSizeGranularity:                            " << value.pointSizeGranularity << "\n";
    out << indent << "lineWidthGranularity:                            " << value.lineWidthGranularity << "\n";
    out << indent << "strictLines:                                     " << value.strictLines << "\n";
    out << indent << "standardSampleLocations:                         " << value.standardSampleLocations << "\n";
    out << indent << "optimalBufferCopyOffsetAlignment:                " << value.optimalBufferCopyOffsetAlignment << "\n";
    out << indent << "optimalBufferCopyRowPitchAlignment:              " << value.optimalBufferCopyRowPitchAlignment << "\n";
    out << indent << "nonCoherentAtomSize:                             " << value.nonCoherentAtomSize << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkPhysicalDeviceSparseProperties const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "residencyStandard2DBlockShape:            " << value.residencyStandard2DBlockShape << "\n";
    out << indent << "residencyStandard2DMultisampleBlockShape: " << value.residencyStandard2DMultisampleBlockShape << "\n";
    out << indent << "residencyStandard3DBlockShape:            " << value.residencyStandard3DBlockShape << "\n";
    out << indent << "residencyAlignedMipSize:                  " << value.residencyAlignedMipSize << "\n";
    out << indent << "residencyNonResidentStrict:               " << value.residencyNonResidentStrict << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkPhysicalDeviceFeatures const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "robustBufferAccess:                      " << value.robustBufferAccess << "\n";
    out << indent << "fullDrawIndexUint32:                     " << value.fullDrawIndexUint32 << "\n";
    out << indent << "imageCubeArray:                          " << value.imageCubeArray << "\n";
    out << indent << "independentBlend:                        " << value.independentBlend << "\n";
    out << indent << "geometryShader:                          " << value.geometryShader << "\n";
    out << indent << "tessellationShader:                      " << value.tessellationShader << "\n";
    out << indent << "sampleRateShading:                       " << value.sampleRateShading << "\n";
    out << indent << "dualSrcBlend:                            " << value.dualSrcBlend << "\n";
    out << indent << "logicOp:                                 " << value.logicOp << "\n";
    out << indent << "multiDrawIndirect:                       " << value.multiDrawIndirect << "\n";
    out << indent << "drawIndirectFirstInstance:               " << value.drawIndirectFirstInstance << "\n";
    out << indent << "depthClamp:                              " << value.depthClamp << "\n";
    out << indent << "depthBiasClamp:                          " << value.depthBiasClamp << "\n";
    out << indent << "fillModeNonSolid:                        " << value.fillModeNonSolid << "\n";
    out << indent << "depthBounds:                             " << value.depthBounds << "\n";
    out << indent << "wideLines:                               " << value.wideLines << "\n";
    out << indent << "largePoints:                             " << value.largePoints << "\n";
    out << indent << "alphaToOne:                              " << value.alphaToOne << "\n";
    out << indent << "multiViewport:                           " << value.multiViewport << "\n";
    out << indent << "samplerAnisotropy:                       " << value.samplerAnisotropy << "\n";
    out << indent << "textureCompressionETC2:                  " << value.textureCompressionETC2 << "\n";
    out << indent << "textureCompressionASTC_LDR:              " << value.textureCompressionASTC_LDR << "\n";
    out << indent << "textureCompressionBC:                    " << value.textureCompressionBC << "\n";
    out << indent << "occlusionQueryPrecise:                   " << value.occlusionQueryPrecise << "\n";
    out << indent << "pipelineStatisticsQuery:                 " << value.pipelineStatisticsQuery << "\n";
    out << indent << "vertexPipelineStoresAndAtomics:          " << value.vertexPipelineStoresAndAtomics << "\n";
    out << indent << "fragmentStoresAndAtomics:                " << value.fragmentStoresAndAtomics << "\n";
    out << indent << "shaderTessellationAndGeometryPointSize:  " << value.shaderTessellationAndGeometryPointSize << "\n";
    out << indent << "shaderImageGatherExtended:               " << value.shaderImageGatherExtended << "\n";
    out << indent << "shaderStorageImageExtendedFormats:       " << value.shaderStorageImageExtendedFormats << "\n";
    out << indent << "shaderStorageImageMultisample:           " << value.shaderStorageImageMultisample << "\n";
    out << indent << "shaderStorageImageReadWithoutFormat:     " << value.shaderStorageImageReadWithoutFormat << "\n";
    out << indent << "shaderStorageImageWriteWithoutFormat:    " << value.shaderStorageImageWriteWithoutFormat << "\n";
    out << indent << "shaderUniformBufferArrayDynamicIndexing: " << value.shaderUniformBufferArrayDynamicIndexing << "\n";
    out << indent << "shaderSampledImageArrayDynamicIndexing:  " << value.shaderSampledImageArrayDynamicIndexing << "\n";
    out << indent << "shaderStorageBufferArrayDynamicIndexing: " << value.shaderStorageBufferArrayDynamicIndexing << "\n";
    out << indent << "shaderStorageImageArrayDynamicIndexing:  " << value.shaderStorageImageArrayDynamicIndexing << "\n";
    out << indent << "shaderClipDistance:                      " << value.shaderClipDistance << "\n";
    out << indent << "shaderCullDistance:                      " << value.shaderCullDistance << "\n";
    out << indent << "shaderFloat64:                           " << value.shaderFloat64 << "\n";
    out << indent << "shaderInt64:                             " << value.shaderInt64 << "\n";
    out << indent << "shaderInt16:                             " << value.shaderInt16 << "\n";
    out << indent << "shaderResourceResidency:                 " << value.shaderResourceResidency << "\n";
    out << indent << "shaderResourceMinLod:                    " << value.shaderResourceMinLod << "\n";
    out << indent << "sparseBinding:                           " << value.sparseBinding << "\n";
    out << indent << "sparseResidencyBuffer:                   " << value.sparseResidencyBuffer << "\n";
    out << indent << "sparseResidencyImage2D:                  " << value.sparseResidencyImage2D << "\n";
    out << indent << "sparseResidencyImage3D:                  " << value.sparseResidencyImage3D << "\n";
    out << indent << "sparseResidency2Samples:                 " << value.sparseResidency2Samples << "\n";
    out << indent << "sparseResidency4Samples:                 " << value.sparseResidency4Samples << "\n";
    out << indent << "sparseResidency8Samples:                 " << value.sparseResidency8Samples << "\n";
    out << indent << "sparseResidency16Samples:                " << value.sparseResidency16Samples << "\n";
    out << indent << "sparseResidencyAliased:                  " << value.sparseResidencyAliased << "\n";
    out << indent << "variableMultisampleRate:                 " << value.variableMultisampleRate << "\n";
    out << indent << "inheritedQueries:                        " << value.inheritedQueries << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkQueueFamilyProperties const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "queueFlags:                  " << queue_flags_to_string(value.queueFlags) << "\n";
    out << indent << "queueCount:                  " << value.queueCount << "\n";
    out << indent << "timestampValidBits:          " << value.timestampValidBits << "\n";
    out << indent << "minImageTransferGranularity: " << value.minImageTransferGranularity << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkExtent3D const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "width:  " << value.width << "\n";
    out << indent << "height: " << value.height << "\n";
    out << indent << "depth:  " << value.depth << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================
