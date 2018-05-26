/**
 * It needs to be compiled, which means it's not as versatile as a json config.
 * It is enough when trying to keep dependencies to a minimum though.
 */

#ifndef ANOTHR_MPD_CONFIG_H
#define ANOTHR_MPD_CONFIG_H

namespace anothr::MpdConfig
{
const static int mpd_port = 6600;
const static char *mpd_address = "localhost";
} // namespace anothr::MpdConfig

#endif