//hColor32.h
#ifndef _hColor32_h_
#define _hColor32_h_

//base type
typedef char            Int8;
typedef unsigned char   UInt8;
typedef short           Int16;
typedef unsigned short  UInt16;
typedef long            Int32; 
typedef unsigned long   UInt32;

//32bitARGB��ɫ����
struct Color32 {
    union {
        UInt32   argb;
        struct
        {
            UInt8  b;
            UInt8  g;
            UInt8  r;
            UInt8  a;
        };
    };
    inline static UInt32 packColor32Data(unsigned long r8,unsigned long g8,unsigned long b8,unsigned long a8=255) { return b8|(g8<<8)|(r8<<16)|(a8<<24);  }
    inline Color32(){}
    inline Color32(const Color32& color32):argb(color32.argb){}
    inline explicit Color32(const UInt32 color32):argb(color32){}
    inline explicit Color32(unsigned long r8,unsigned long g8,unsigned long b8,unsigned long a8=255):argb(packColor32Data(r8,g8,b8,a8)){}
    inline bool operator ==(const Color32& color32) const { return argb==color32.argb; }
    inline bool operator !=(const Color32& color32) const{ return !((*this)==color32); }
};


//ͼ����������������Ϣ
struct TPixels32Ref{
    Color32*    pdata;        //ͼ���������׵�ַ  �� y==0�е���ɫ�׵�ַ
    long        byte_width;   //һ��ͼ�����ݵ��ֽڿ��  ����ֵ���п��� 
    long        width;        //ͼ����
    long        height;       //ͼ��߶�
    inline TPixels32Ref() :pdata(0),byte_width(0),width(0),height(0){}
    inline TPixels32Ref(const TPixels32Ref& ref) :pdata(ref.pdata),byte_width(ref.byte_width),width(ref.width),height(ref.height){}
    
    //����(x,y)���괦����ɫ
    inline Color32& pixels(const long x,const long y) const { return getLinePixels(y)[x]; }
    //�õ�y�е���ɫ�׵�ַ
    inline Color32* getLinePixels(const long y) const { return (Color32*) ( ((UInt8*)pdata) + byte_width*y ); }

    //�Ƿ��ǿ�ͼ����
    inline bool getIsEmpty()const { return ((width<=0)||(height<=0)); }
    //��plineָ����һ����ɫ
    inline void nextLine(Color32*& pline)const {  ((UInt8*&)pline)+=byte_width;   }

    //����߽籥��  ���(x,y)������ͼƬ��������,(x,y)ֵ�ᱻ���õ�ͼƬ����ı߽���,������false(����ʲôҲ����,����true) //����! ͼƬ������Ϊ��
    inline bool clipToBorder(long& x, long& y)const{
        bool isIn = true;
        if (x < 0) { 
            isIn = false; x = 0;
        } else if (x >= width) { 
            isIn = false; x = width - 1;
        }
        if (y < 0) {
            isIn = false; y = 0;
        } else if (y >= height) {
            isIn = false; y = height - 1;
        }
        return isIn;
    }
    //��ȡһ�������ɫ,Ĭ��ִ�б߽籥�Ͳ���  �����곬�������ʱ�򷵻ص���ɫΪ����ı߽��ϵ���ɫֵ������alphaͨ������  //����! ͼƬ������Ϊ�� �ٶȺ��� 
    inline Color32 getPixelsBorder(long x, long y) const {
        bool isInPic = clipToBorder(x,y);
        Color32 result = pixels(x,y);
        if (!isInPic)
            result.a=0;
        return result;
    }
    inline bool getIsInPic(long x, long y)const{
        //return (x>=0)&&(y>=0)&&(x<width)&&(y<height);
        //���ø����ı����Ż�Ϊ:
        return ((unsigned long)x<(unsigned long)width)&&((unsigned long)y<(unsigned long)height);
    }

    //�����ɫ
    void fillColor(const Color32 color)const{
        Color32* pDstLine=(Color32*)pdata;
        for (long y=0;y<height;++y){
            for (long x=0;x<width;++x){
                pDstLine[x]=color;
            }
            nextLine(pDstLine);
        }
    }
    void fillAlpha(const unsigned int alpha)const {
        Color32* pDstLine=(Color32*)pdata;
        for (long y=0;y<height;++y){
            for (long x=0;x<width;++x){
                pDstLine[x].a=alpha;
            }
            nextLine(pDstLine);
        }
    }
    void copyColor(const TPixels32Ref& src)const{
        Color32* pDstLine=(Color32*)pdata;
        Color32* pSrcLine=(Color32*)src.pdata;
		long mHeight=height;
		if (mHeight>src.height) mHeight=src.height;
		long mWidth=width;
		if (mWidth>src.width) mWidth=src.width;
        for (long y=0;y<mHeight;++y){
            for (long x=0;x<mWidth;++x){
                pDstLine[x]=pSrcLine[x];
            }
            nextLine(pDstLine);
            src.nextLine(pSrcLine);
        }
    }
};

//ͼ���������ӿ�
class IPixels32Buf{
public:
    virtual void resizeFast(long width,long height)=0;    //����ͼ����������С
    virtual bool lockBuf(TPixels32Ref& out_color32Ref)=0;  //��ס���� ������������Ϣ
    virtual void unlockBuf()=0; //��������
    virtual ~IPixels32Buf(){}
};

#endif
