struct StringArray {
    int length;
    const char **array;
};

extern void StringArray_new(struct StringArray *this);
extern void StringArray_add(struct StringArray *this, const char *string);
extern void StringArray_delete(struct StringArray *this);
