#pragma once

#include "core/serialization/serialization.h"
#include "core/serialization/cereal/types/string.hpp"
#include "core/common/string.h"
#include "core/logging/logging.h"
#include "../../assets/asset_handle.h"
#include "../../assets/asset_manager.h"
#include "../../rendering/mesh.h"
#include "../../rendering/texture.h"
#include "../../rendering/material.h"
#include "../../ecs/prefab.h"
#include "../../ecs/scene.h"

namespace cereal
{

	template<typename Archive, typename T>
	inline void SAVE_FUNCTION_NAME(Archive & ar, AssetLink<T> const& obj)
	{
		try_save(ar, cereal::make_nvp("id", obj.id));
	}


	template<typename Archive, typename T>
	inline void LOAD_FUNCTION_NAME(Archive & ar, AssetLink<T>& obj)
	{
		try_load(ar, cereal::make_nvp("id", obj.id));
	}


	template<typename Archive, typename T>
	inline void SAVE_FUNCTION_NAME(Archive & ar, AssetHandle<T> const& obj)
	{
		try_save(ar, cereal::make_nvp("link", obj.link));
	}

	template<typename Archive, typename T>
	inline void LOAD_FUNCTION_NAME(Archive & ar, AssetHandle<T>& obj)
	{
		try_load(ar, cereal::make_nvp("link", obj.link));

		if (obj.link->id.empty())
		{
			obj = AssetHandle<T>();
		}
		else
		{
			auto am = core::get_subsystem<runtime::AssetManager>();
			am->load<T>(obj.link->id, false)
				.then([&obj](auto asset) mutable
			{
				obj = asset;
			});
		}
	}
}