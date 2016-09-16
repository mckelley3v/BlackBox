#include "vku_device.hpp"
#include "vku_utility.hpp"

// ====================================================================================================================

/*explicit*/ vku::Device::Device(VkDevice const device)
   : m_VkDevice(device)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device::Device(Device &&rhs)
   : m_VkDevice(rhs.m_VkDevice)
{
   rhs.m_VkDevice = VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device& vku::Device::operator = (Device &&rhs)
{
   m_VkDevice = rhs.m_VkDevice;
   rhs.m_VkDevice = VK_NULL_HANDLE;
   return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device::~Device()
{
   if(m_VkDevice != VK_NULL_HANDLE)
   {
      vkDestroyDevice(m_VkDevice, // pDevice
                      nullptr); // pAllocator
   }
}

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ vku::Device::operator bool() const
{
   return m_VkDevice != VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device::operator VkDevice() const
{
   return m_VkDevice;
}

// ====================================================================================================================

//VkDevice vku::CreateDevice(VkInstance instance,
//                           PhysicalDeviceQueueFamily physicalDeviceQueueFamily)

// ====================================================================================================================

vku::DeviceProcBase::DeviceProcBase(VkDevice const device,
                                    char const * const func_name)
    : m_FuncPtr(vkGetDeviceProcAddr(device, func_name))
{
    if(m_FuncPtr == nullptr)
    {
        throw std::runtime_error(make_string({"error: vkGetDeviceProcAddr(\"", func_name, "\") returned nullptr"}));
    }
}

// ====================================================================================================================
