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
        ~JSONObject(){};
        JSONObject *value;
        DataType dataType;
    };
}