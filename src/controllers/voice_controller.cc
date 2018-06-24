#include <iostream>

#include <Python.h>

#include "voice_controller.hh"

namespace anothr
{

void VoiceController::runVoiceRecognition()
{
	// char filename[] = "speech_request_client.py";
	char file_path[] = "speech_processing/speech_request_client.py";

	// wchar_t *program = Py_DecodeLocale(filename, NULL);

	// if (program == NULL)
	// {
	// 	std::cout << "Error decoding program name" << std::endl;
	// }
	// Py_SetProgramName(program);
	Py_Initialize();

	FILE *fp = _Py_fopen(file_path, "r");

	PyRun_SimpleFile(fp, file_path);
	Py_Finalize();
	// PyMem_RawFree(program);
}

} // namespace anothr