#ifndef _DS_PROJECT_H_ 
#define _DS_PROJECT_H_
#include <vector>
#include <string>

class DsSprite;
class DsAnimation;
class DsFrameImage;
class DsFrame;
class DsKeyFrame;

#define DS_DEFAULT_UNDO_SIZE 512

class DsProject 
{
public:
    class DsSpriteState
    {
    public:
        DsSprite* m_sprite;
        DsAnimation* m_curAnimation;
        DsFrameImage* m_curFrameImage;
        int m_curFrameIndex;


    public:
        DsSpriteState(DsSprite* sprite,
                      DsAnimation* cur_animation,
                      DsFrameImage* cur_frameimg,
                      int frame_index);
        ~DsSpriteState();
    };
    class CircleQueue
    {

    public:
        CircleQueue();
        ~CircleQueue();
        void push(DsSpriteState* state);
        void pushFrontTail(DsSpriteState* state);
        DsSpriteState* get(int i);
        int size();
        bool full();
        bool empty();
        void dropTail(int nu);
    private:
        DsSpriteState* m_queue[DS_DEFAULT_UNDO_SIZE];
        int m_used;
        int m_begin;
    };

    class DsSpriteInfo
    {
    public:
        DsSprite* getSprite();
        void setCurAnimation(const std::string& id);
        void setCurFrameIndex(int index);
        void setCurFrameImage(const std::string& id);

        void dropCurAnimation();
        void dropCurFrameIndex();
        void dropCurFrameImage();

        DsAnimation* getCurAnimation();
        DsFrameImage* getCurFrameImage();
        DsFrame* getCurFrame();
        int getCurFrameIndex();

        /* copy and past */

        /* frame image */
        DsFrameImage* getCopyFrameImage(){return m_copyFrameImage;}
        void setCopyFrameImage(DsFrameImage* image);

        /* frame */
        void setCopyFrame(DsKeyFrame* frame);
        DsKeyFrame* getCopyFrame(){return m_copyFrame;}


        DsSpriteInfo(DsSprite* sprite);
        ~DsSpriteInfo();

        /* extends for undo/redo */
    public:
        void pushState();
        void redo();
        void undo();
        bool canRedo();
        bool canUndo();
    protected:
        void restore(DsSpriteState* state);
    private:
        CircleQueue m_queue;
        int m_curStateIndex;

        /* copy and paste */
        DsFrameImage* m_copyFrameImage;
        DsKeyFrame* m_copyFrame;

    };

public:
    static DsProject* loadFromFile(const std::string& filename);

public:
    DsProject();
    ~DsProject();
public:
    std::string getDirName(){return m_dirName;}
    std::string getFileName(){return m_fileName;}
    void setDirName(const std::string& name){m_dirName=name;}
    void setFileName(const std::string& name){m_fileName=name;}

public:
    /* animation */
    void addSprite(DsSprite* sprite);
    void removeSprite(const std::string& id);
    bool hasSpriteWithName(const std::string& name);

    DsSprite* getCurSprite();
    DsSpriteInfo* getCurSpriteInfo(){return m_curSprite;}
    void setCurSprite(const std::string& id);


    /* animation*/
    DsAnimation* getCurAnimation();
    void setCurAnimation(const std::string& id);
    void dropCurAnimation();

    /* frame */
    DsFrame* getCurFrame();
    int getCurFrameIndex();
    void setCurFrameIndex(int framenu);
    void dropCurFrameIndex();

    /* frame image */
    DsFrameImage* getCurFrameImage();
    void setCurFrameImage(const std::string& name);
    void dropCurFrameImage();
public:
    DsSprite* getSprite(int index);
    int getSpriteNu(){return m_sprites.size();}

    DsSprite* getSprite(const std::string& id);

private:
    DsSpriteInfo* m_curSprite;
    std::vector<DsSpriteInfo*> m_sprites;

    std::string m_dirName;
    std::string m_fileName;
};

#endif /*_DS_PROJECT_H_*/
























