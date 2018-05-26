#include <iostream>

#include <Python.h>

#include "voice_controller.hh"

namespace anothr
{

void VoiceController::listen()
{
	char filename[] = "natural_language_interface/main_cpp.py";
	FILE *fp;
	wchar_t *program = Py_DecodeLocale("main_cpp.py", NULL);

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
}

} // namespace anothr