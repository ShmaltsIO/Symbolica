#ifndef IREADER_H
#define IREADER_H

/**
 * @brief Interface for reading some information from special files.
 */
template<typename T>
class IReader {
protected:
    virtual ~IReader() = default;
public:
// TODO: make this function a template, because it can return chat, or string (if dialog)...
    virtual T read() = 0;

    IReader& operator=(const IReader&) = delete;
};

#endif // IREADER_H