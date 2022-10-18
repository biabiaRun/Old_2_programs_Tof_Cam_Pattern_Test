/****************************************************************************\
 * Copyright (C) 2019 pmdtechnologies ag & Infineon Technologies
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#include <storage/SpiBusMasterM2457.hpp>
#include <imager/M2457/ImagerRegisters.hpp>

#include <royale/Vector.hpp>

#include <chrono>

// \todo: ROYAL-2908 dependencies between the components

using namespace royale;
using namespace royale::common;
using namespace royale::storage;

SpiBusMasterM2457::SpiBusMasterM2457 (std::shared_ptr<royale::hal::IBridgeImager> access) : SpiBusMasterFlashBasedDevice (access)
{
    m_transmitRequiresReadEnabled = false;

    m_registers.SPI_WR_ADDR = royale::imager::M2457::SPIWRADDR;
    m_registers.SPI_RD_ADDR = royale::imager::M2457::SPIRADDR;
    m_registers.SPI_LEN = royale::imager::M2457::SPILEN;
    m_registers.SPI_TRIG = royale::imager::M2457::SPITRIG;
    m_registers.SPI_STATUS = royale::imager::M2457::SPISTATUS;
    m_registers.SPI_CFG = royale::imager::M2457::SPICFG;
}

void SpiBusMasterM2457::initializeOnce()
{
    // Reset the imager to be sure it's in a known state
    m_imager->setImagerReset (true);
    m_imager->sleepFor (std::chrono::microseconds (1));
    m_imager->setImagerReset (false);

    // No additional firmware is required, the existing ROM firmware is sufficient.  The SPI_CFG write
    // enables it and sets the clock divisor as expected.
    const auto spiEnable = 1u << 14;
    const auto spiPolarity = 1u << 12;
    const auto spiClockDiv8 = 2u;
    m_imager->writeImagerRegister (m_registers.SPI_CFG, static_cast<uint16_t> (spiEnable | spiPolarity | spiClockDiv8));
}

SpiBusMasterM2457::~SpiBusMasterM2457()
{
}