#include "voice_controller.hh"

namespace Othr
{

VoiceController::VoiceController() {}
/**
 * Fetches the current playlist by sending a "send" request to the mpd server, and then iterating over the received songs to extract their relevant information into an easily usable format.
 */
void VoiceController::listen()
{
	char filename[] = "speech_processing/main.py";
	FILE *fp;
	wchar_t *program = Py_DecodeLocale("main.py", NULL);

	if (program == NULL)
	{
		std::cout << "Error decoding program name" << std::endl;
	}
	Py_SetProgramName(program);
	Py_Initialize();
	fp = _Py_fopen(filename, "r");

	PyRun_SimpleFile(fp, filename);
	Py_Finalize();
	PyMem_RawFree(program);
	// std::cout << "Printing in c++" << std::endl;
}

} // namespace Othr