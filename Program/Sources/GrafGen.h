typedef struct Attribute {
    char key[64];
    char value[64]
} Attribute;
typedef struct XElement {
    char elementName[64]
    char elementValue[64]
    Attribute *attributes;
    int attributeCount;
    XElement *children;
    int childCount;
} XElement;
typedef struct XDoc {
    char filename[64];
} XDoc;