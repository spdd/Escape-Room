#ifndef __LevelManager__
#define __LevelManager__
class LevelManager
{
    public:
        static LevelManager* getInstance();
    
    protected:
        static LevelManager* mInstance;
        
    private:
        LevelManager();
        ~LevelManager();
};
#endif