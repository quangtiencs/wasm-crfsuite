#include <emscripten/bind.h>
#include <crfsuite_api.hpp>
#include <string>
#include <iostream>
#include <optional>

using namespace emscripten;

class AttributeCRF
{
public:
    CRFSuite::Attribute attr;

    AttributeCRF(std::string name, double value) : attr(name, value) {}
    AttributeCRF(std::string name) : attr(name) {}
    AttributeCRF() : attr() {}
};

class ItemCRF
{
public:
    CRFSuite::Item it;

    ItemCRF() : it() {}
    auto addAttribute(const AttributeCRF &attribute) -> void
    {
        it.push_back(attribute.attr);
    }
};

class ItemSequenceCRF
{
public:
    CRFSuite::ItemSequence itsequence;

    ItemSequenceCRF() : itsequence() {}
    auto addItem(const ItemCRF &item) -> void
    {
        itsequence.push_back(item.it);
    }
};

class ModelCRF
{
public:
    std::string modelPath;
    CRFSuite::Tagger model;

    ModelCRF(std::string filePath) : modelPath{filePath}
    {
        model.open(modelPath);
    }

    auto labels() -> std::vector<std::string>
    {
        return model.labels();
    }

    auto tag(const ItemSequenceCRF &itemsequence) -> std::vector<std::string>
    {
        return model.tag(itemsequence.itsequence);
    }
};

EMSCRIPTEN_BINDINGS(crf_module)
{
    register_vector<std::string>("vector<std::string>");
    class_<ModelCRF>("ModelCRF")
        .constructor<std::string>()
        .function("tag", &ModelCRF::tag)
        .function("labels", &ModelCRF::labels);
    class_<AttributeCRF>("AttributeCRF")
        .constructor<>()
        .constructor<std::string>()
        .constructor<std::string, double>();
    class_<ItemCRF>("ItemCRF")
        .constructor<>()
        .function("addAttribute", &ItemCRF::addAttribute);
    class_<ItemSequenceCRF>("ItemSequenceCRF")
        .constructor<>()
        .function("addItem", &ItemSequenceCRF::addItem);
}

int main()
{
    std::cout << "[wasm-crfsuite] Initialization." << std::endl;
    return 1;
}
