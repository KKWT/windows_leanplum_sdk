#pragma once

#define MESSAGE_BASED (WM_USER + 1)

class MessageCode
{
public:
	enum MESSAGE_CODE {
		MESSAGE_LOGIN = MESSAGE_BASED,
		MESSAGE_SEARCH_FINISH,
		MESSAGE_EXECUTE_SONG_DATA,
		MESSAGE_INSERT_DATABASE_DATA_FINISH,
		MESSAGE_HTTP_STATUS_OK,
		MESSAGE_HTTP_STATUS_NOT_OK,
		MESSAGE_DOWNLOADING_DATA,
		MESSAGE_DOWNLOAD_FINISH,
		MESSAGE_GET_TICKET_FINISH,
		MESSAGE_SID_WRITE,
		MESSAGE_SID_CLEAR,
		MESSAGE_UPDATE_LIKE_DISLIKE_BTNS,
		MESSAGE_PRELOAD_FREE_FINISH,
		MESSAGE_GET_MUSIC_HQ_LIST_FINISH,
		MESSAGE_PLAYLIST_CHECK_OK,
		MESSAGE_PLAYLIST_CHECK_FAILD,
		MESSAGE_PLAYLIST_CHECK_CANCEL,
		MESSAGE_PLAYLIST_SHARE_OK,
		MESSAGE_PLAYLIST_SHARE_FAILD,
		MESSAGE_PLAYLIST_SHARE_CANCEL,
		MESSAGE_GETVARS_FINISH,
		MESSAGE_START_FINISH,
		MESSAGE_STOP_FINISH,
		MESSAGE_SETVARS_FINISH,
		MESSAGE_GETABTESTS_FINISH,
		MESSAGE_GETABTEST_FINISH
	};
};
