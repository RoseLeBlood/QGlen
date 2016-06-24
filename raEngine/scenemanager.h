#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "iobject.h"
#include "list"

class QPainter;

class RAENGINESHARED_EXPORT SceneManager
{
public:
    SceneManager(GameWindow* pWnd);

    virtual bool Initialize()
    {
        for (std::list<IObject*>::iterator item = m_GameStates.begin();
             item != m_GameStates.end();
             item++)
        {
            IObject* object = ((IObject*)(*item));
            if(object != NULL)
            {
                object->Initialize();
            }
        }
        return true;
    }
    virtual bool Destroy()
    {
        for (std::list<IObject*>::iterator item = m_GameStates.begin();
             item != m_GameStates.end();
             item++)
        {
            IObject* object = ((IObject*)(*item));
            if(object != NULL)
            {
                object->Destroy();
            }
        }

        m_GameStates.clear();

        return true;
    }

    virtual bool Render(QPainter *painter, double smoothStep)
    {
        for(int i= 0; i < SceneManagerPrio::MAX; i++)
        {
            for (std::list<IObject*>::iterator item = m_GameStates.begin();
                 item != m_GameStates.end();
                 item++)
            {
                IObject* object = ((IObject*)(*item));
                if(object != NULL)
                {
                    if( object->Prio() == i)
                    {
                        if(object->CanDraw())
                            object->Render(painter, smoothStep);
                    }
                }
            }
        }
        return true;
    }

    virtual bool Move(double renderTime, double elapsedTime)
    {
        for (std::list<IObject*>::iterator item = m_GameStates.begin();
             item != m_GameStates.end();
             item++)
        {
            IObject* object = ((IObject*)(*item));
            if(object != NULL )
            {
                if(object->CanUpdate())
                    object->Move(renderTime, elapsedTime);
            }
        }
        return true;
    }
    virtual bool Input()
    {
        for (std::list<IObject*>::iterator item = m_GameStates.begin();
             item != m_GameStates.end();
             item++)
        {
            IObject* object = ((IObject*)(*item));
            if(object != NULL )
            {
                if(object->CanUpdate())
                    object->Input();
            }
        }
        return true;
    }
    void AddObjectToScene(IObject* obj)
    {
        m_GameStates.push_back(obj);
    }
    GameWindow* GetGameWindow() { return m_pWnd; }
protected:
     GameWindow* m_pWnd;
private:
     std::list<IObject*>  m_GameStates;
};

#endif // SCENEMANAGER_H
