#pragma once
//This is basically our modelInstance class 
class Object {
  public:
    Object(int id /*TODO: add position (vec3) and graphics*/);
    ~Object() = default;

  private:
    // TODO: add graphics
    int objectID;
};
