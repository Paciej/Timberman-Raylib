#ifndef SCENE_H_
#define SCENE_H_

class Scene {
public:
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual bool ShouldTransition() const { return false; }
    virtual Scene* NextScene() const { return nullptr; }
    virtual ~Scene() {}
};
#endif // !SCENE_H_


