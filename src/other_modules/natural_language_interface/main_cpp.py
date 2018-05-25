import sys
sys.path.append('./')
sys.path.append('./natural_language_interface')

import json
import requests
import os

from speech_control.speech_to_text import SpeechToText
from speech_control.text_to_speech import TextToSpeech

if __name__ == '__main__':

    try:
        print(os.getcwd())
        with open(os.getcwd() + '/natural_language_interface/configs/configuration.json') as json_file:
            json_data = json.load(json_file)

        BING_KEY = json_data.get('Bing_Key')
        url_server = "http://127.0.0.1:5000"

        stt = SpeechToText(bing_key=BING_KEY, mode='interactive', language='united_states')
        stt_resp = stt.start_recognize(recognizer='listen')

        if 'DisplayText' in stt_resp:
            print(stt_resp['DisplayText'])
            #send stt response to parse_server
            requests.post(url=url_server, data=stt_resp['DisplayText'])

        else:
            print("Did not understand, please retry")

    except FileNotFoundError as e:
        print(str(e))
    except KeyError as e:
        print(str(e) + " is not defined in config.json")
