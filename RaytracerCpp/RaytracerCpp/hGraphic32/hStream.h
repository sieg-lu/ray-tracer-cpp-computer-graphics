//hStream.h

#ifndef _hStream_h_
#define _hStream_h_
#include <stdexcept>//exception
#include <string>

//������
class IInputStream{
public:
    virtual void* read(long bCount)=0;
    virtual void  read(void* Dst,long bCount)=0;
    virtual bool  try_read(void* Dst,long bCount)const=0; //���Զ�һС�����ݣ������ƶ���ָ��
    virtual void  skip(unsigned long bCount)=0;
    virtual ~IInputStream(){}
};

//������������
class IBufInputStream:public IInputStream{
public:
    virtual long getSize()const=0;
    virtual long getPos()const=0;
    virtual void setPos(long pos)=0;
};

//�����
class IOutputStream{
public:
    virtual void write(const void* SrcBuf,long bCount)=0;
    virtual ~IOutputStream(){}
};

/////////////////////////////////////////////////////////////////////////////////////////////

struct TFileInputStreamError:public std::runtime_error{
    TFileInputStreamError(const std::string& error) :std::runtime_error(error){}
};

//�ļ�������
class TFileInputStream:public IBufInputStream{
private:
    void*           m_fileHandle;
    unsigned char*  m_buf;
    long            m_bufSize;
    inline void throwException(const std::string& error){
        throw TFileInputStreamError(error);
    }
    void resizeBuf(long bufSize);
public:
    TFileInputStream(const char* fileName);
    virtual ~TFileInputStream();
    virtual long getSize()const;
    virtual long getPos()const;
    virtual void setPos(long pos);

    virtual void* read(long bCount);
    virtual void  read(void* Dst,long bCount);
    virtual bool  try_read(void* Dst,long bCount)const; //���Զ�һС�����ݣ������ƶ���ָ��
    virtual void  skip(unsigned long bCount);
};


struct TFileOutputStreamError:public std::runtime_error{
    TFileOutputStreamError(const std::string& error) :std::runtime_error(error){}
};

//�ļ������
class TFileOutputStream:public IOutputStream{
private:
    void*           m_fileHandle;
    inline void throwException(const std::string& error){
        throw TFileOutputStreamError(error);
    }
public:
    TFileOutputStream(const char* aFileName);
    virtual ~TFileOutputStream();
    virtual void write(const void* Src,long bCount);
};

#endif //_hStream_h_
