#include "animator.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "bone.hpp"

Animator::Animator(Animation* animation) : animation(animation) {
    boneMatrices.resize(animation->getBoneCount(), glm::mat4(1.0f));
}

void Animator::setAnimation(Animation* animation) {
    this->animation = animation;
    currentTime = 0.0f;

    if (animation->getBoneCount() > boneMatrices.size()) {
        boneMatrices.resize(animation->getBoneCount());
    }
}

void Animator::update(float deltaTime) {
    float speedMultiplier = 2.0f;

    currentTime += deltaTime * animation->getTicksPerSecond() * speedMultiplier;
    currentTime = fmod(currentTime, animation->getDuration());

    computeBoneTransform(animation->getRootNode(), glm::mat4(1.0f));
}

void Animator::computeBoneTransform(const aiNode* node, const glm::mat4& parentTransform) {
    std::string nodeName = node->mName.C_Str();
    glm::mat4 nodeTransform = glm::transpose(glm::make_mat4(&node->mTransformation.a1));
    glm::mat4 globalTransform;

    Bone* bone = animation->findBone(nodeName);

    if (bone) {
        bone->update(currentTime);
        globalTransform = parentTransform * bone->getTransform();
        boneMatrices[bone->getID()] =
            globalTransform * animation->getModel()->getBoneOffsets()[bone->getID()];
    } else {
        globalTransform = parentTransform * nodeTransform;
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        computeBoneTransform(node->mChildren[i], globalTransform);
    }
}
