#ifndef GAME_MWWORLD_GLOBALS_H
#define GAME_MWWORLD_GLOBALS_H

#include <string>
#include <unordered_map>
#include <vector>

#include <cstdint>

#include <components/esm3/loadglob.hpp>
#include <components/misc/strings/algorithm.hpp>

namespace ESM
{
    class ESMWriter;
    class ESMReader;
}

namespace Loading
{
    class Listener;
}

namespace MWWorld
{
    class ESMStore;

    class Globals
    {
    private:
        using Collection
            = std::unordered_map<std::string, ESM::Global, Misc::StringUtils::CiHash, Misc::StringUtils::CiEqual>;

        Collection mVariables; // type, value

        Collection::const_iterator find(std::string_view name) const;

        Collection::iterator find(std::string_view name);

    public:
        const ESM::Variant& operator[](std::string_view name) const;

        ESM::Variant& operator[](std::string_view name);

        char getType(std::string_view name) const;
        ///< If there is no global variable with this name, ' ' is returned.

        void fill(const MWWorld::ESMStore& store);
        ///< Replace variables with variables from \a store with default values.

        int countSavedGameRecords() const;

        void write(ESM::ESMWriter& writer, Loading::Listener& progress) const;

        bool readRecord(ESM::ESMReader& reader, uint32_t type);
        ///< Records for variables that do not exist are dropped silently.
        ///
        /// \return Known type?
    };
}

#endif
