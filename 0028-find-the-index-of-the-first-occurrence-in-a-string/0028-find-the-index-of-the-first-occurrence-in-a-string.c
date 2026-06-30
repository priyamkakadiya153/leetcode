int strStr(char* haystack, char* needle) { 
    char* pointer = strstr(haystack,needle); 
    if (pointer != NULL) { 
        int index = pointer - haystack; 
        return index; 
    } 
    else 
    return -1; 
} 