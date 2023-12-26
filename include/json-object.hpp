#pragma once
#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

namespace octo_data
{
    enum DataType
    {
        String,
        Int,
        Object,
        Array
    };

    class JSONObject
    {
    public:
        JSONObject(DataType dType) : dataType(dType){};
        ~JSONObject();
        JSONObject *value;
        DataType dataType;
    };
};

#endif