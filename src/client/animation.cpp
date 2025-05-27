#include "animation.hpp"
#include <assimp/anim.h>

Animation::Animation(const aiScene* scene, AnimatedModel* model) : model(model) {
    rootNode = scene->mRootNode;
    const aiAnimation* animation = scene->mAnimations[0];

    duration = static_cast<float>(animation->mDuration);
    ticksPerSecond =
        static_cast<float>(animation->mTicksPerSecond != 0.0 ? animation->mTicksPerSecond : 30.0);

    for (unsigned int i = 0; i < animation->mNumChannels; ++i) {
        aiNodeAnim* channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.C_Str();

        if (model->hasBone(boneName)) {
            bones.emplace(boneName, Bone(boneName, model->getBoneID(boneName), channel));
        }
    }
}

Bone* Animation::findBone(const std::string& name) {
    return bones.contains(name) ? &bones.at(name) : nullptr;
}
