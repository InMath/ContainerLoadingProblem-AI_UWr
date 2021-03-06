#include "ContainerLoader.h"

namespace ContainerLoading
{
    ContainerLoader::ContainerLoader(const Utils::Container container, IPackageGenerator* packageGenerator)
        : _container(container)
    {
        _packages = packageGenerator->generatePackages();
        _algorithm = nullptr;
    }

    ContainerLoader::~ContainerLoader()
    {
        if(_algorithm != nullptr)
        {
            delete _algorithm;
        }
    }
    
    bool ContainerLoader::run(int steps)
    {
        if(_algorithm != nullptr)
        {
            return _algorithm->run(steps);
        }
        return false;
    }

    bool ContainerLoader::singleStep()
    {
        return run(1);
    }

    unsigned ContainerLoader::countUnloadedPackages() const
    {
        if(_algorithm != nullptr)
            return _algorithm->countUnloadedPackages();

        return _packages.size();
    }

    unsigned ContainerLoader::countLadedPackages() const
    {
        return _container.countContainingPackages();
    }

    Utils::Container& ContainerLoader::getContainer()
    {
        return _container;
    }

    std::vector<Utils::Package>& ContainerLoader::getPackages()
    {
        return _packages;
    }

    glm::float32 ContainerLoader::getBestLoadingCapacity() const
    {
        if(_algorithm != nullptr)
            return _algorithm->getBestLoadingCapacity();

        return 0;
    }

    unsigned ContainerLoader::getBestLoadingNbOfPackages() const
    {
        if(_algorithm != nullptr)
            return _algorithm->getBestLoadingNbOfPackages();

        return 0;
    }

    void ContainerLoader::applyAlgorithm(Algorithm::IAlgorithm* algorithm)
    {
        if(_algorithm != nullptr)
            delete _algorithm;

        _algorithm = algorithm;
    }
}