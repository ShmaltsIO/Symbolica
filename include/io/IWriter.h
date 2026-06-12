#ifndef IWRITER_H
#define IWRITER_H

/**
 * @brief Interface for writing some information to special files.
 */
template<typename T>
class IWriter {
protected:
    virtual ~IWriter() = default;
public:
    virtual void write(T) = 0;

    IWriter& operator=(const IWriter&) = delete;
};

#endif // IWRITER_H