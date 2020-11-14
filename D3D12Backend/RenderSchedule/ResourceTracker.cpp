#include "stdafx.h"
#include "ResourceTracker.h"
#include "APIWrappers/Resources/ResourceTransition.h"

namespace Boolka
{

    ResourceTracker::~ResourceTracker()
    {
        BLK_ASSERT(m_TrackedResources.empty());
    }

    bool ResourceTracker::Initialize(Device& device, size_t expectedResources)
    {
        m_TrackedResources.reserve(expectedResources);

        return true;
    }

    void ResourceTracker::Unload()
    {
        m_TrackedResources.clear();
    }

    void ResourceTracker::RegisterResource(Resource& resource, D3D12_RESOURCE_STATES initialState)
    {
        auto [resourceIterator, isInserted] = m_TrackedResources.insert({ &resource, initialState });
        BLK_ASSERT(isInserted);
    }

    bool ResourceTracker::Transition(Resource& resource, CommandList& commandList, D3D12_RESOURCE_STATES targetState)
    {
        auto iterator = m_TrackedResources.find(&resource);
        BLK_ASSERT(iterator != m_TrackedResources.end());

        // TODO decide if need to handle unknown resource
        if (iterator == m_TrackedResources.end())
            return false;

        D3D12_RESOURCE_STATES sourceState = iterator->second;

        if (!ResourceTransition::NeedTransition(sourceState, targetState))
            return false;
        if (!ResourceTransition::CanPromote(sourceState, targetState))
            ResourceTransition::Transition(resource, commandList, sourceState, targetState);
        iterator->second = targetState;

        return true;
    }

    void ResourceTracker::Decay()
    {
        for (auto& [resource, state] : m_TrackedResources)
        {
            if (ResourceTransition::CanDecay(state))
                state = D3D12_RESOURCE_STATE_COMMON;
        }
    }

}
