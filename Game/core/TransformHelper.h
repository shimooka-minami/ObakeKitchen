#pragma once
#include <tuple>

namespace json
{
    struct Transform
    {
        Vector3 position;
        Vector3 scale;
        Quaternion rotation;
    };


    static Vector3 ParseVector3(const nlohmann::json& j)
    {
        return Vector3(j.at("x").get<float>(), j.at("y").get<float>(), j.at("z").get<float>());
    }


    static Quaternion ParseQuaternion(const nlohmann::json& j)
    {
        return Quaternion(j.at("x").get<float>(), j.at("y").get<float>(), j.at("z").get<float>(), j.at("w").get<float>());
    }


    static Transform ParseTransformComponents(const nlohmann::json& transformJson)
    {
        Transform transform;
        transform.position = ParseVector3(transformJson.at("position"));
        transform.rotation = ParseQuaternion(transformJson.at("rotation"));
        transform.scale = ParseVector3(transformJson.at("scale"));
        return transform;
    }

}