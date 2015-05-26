#pragma once
#include <hash_map>
#define LEANPLUM_HOST _T("http://www.leanplum.com/api")
#define LEANPLUM_API_VERSION _T("1.0.6")

class AbTestVariants
{
public:
	INT64 m_id;
	int m_percent;
	CString m_name;

	void DataParse(json::value jval)
	{
		std::hash_map<TCHAR*, int*> key_int;
		key_int[_T("percent")] = &m_percent;
		for (std::hash_multimap<TCHAR*, int*>::iterator it = key_int.begin(); it != key_int.end(); it++) {
			if (!jval.at(it->first).is_null()) {
				*it->second = jval.at(it->first).as_integer();
			}
		}

		std::hash_map<TCHAR*, INT64*> key_int64;
		key_int64[_T("id")] = &m_id;
		for (std::hash_multimap<TCHAR*, INT64*>::iterator it = key_int64.begin(); it != key_int64.end(); it++) {
			if (!jval.at(it->first).is_null()) {
				*it->second = jval.at(it->first).as_number().to_int64();
			}
		}

		std::hash_map<TCHAR*, CString*> key_cstr;
		key_cstr[_T("name")] = &m_name;
		for (std::hash_multimap<TCHAR*, CString*>::iterator it = key_cstr.begin(); it != key_cstr.end(); it++) {
			if (!jval.at(it->first).is_null()) {
				*it->second = jval.at(it->first).as_string().c_str();
			}
		}
	}
};

class AbTestInfo
{
public:
	bool m_active;
	std::vector<AbTestVariants> m_abTestVariants;
	double m_created;
	INT64 m_id;
	CString m_name;

	void DataParse(json::value jval)
	{
		std::hash_map<TCHAR*, bool*> key_bool;
		key_bool[_T("active")] = &m_active;
		for (std::hash_multimap<TCHAR*, bool*>::iterator it = key_bool.begin(); it != key_bool.end(); it++) {
			if (!jval.at(it->first).is_null()) {
				*it->second = jval.at(it->first).as_bool();
			}
		}

		std::hash_map<TCHAR*, double*> key_double;
		key_double[_T("created")] = &m_created;
		for (std::hash_multimap<TCHAR*, double*>::iterator it = key_double.begin(); it != key_double.end(); it++) {
			if (!jval.at(it->first).is_null()) {
				*it->second = jval.at(it->first).as_double();
			}
		}

		std::hash_map<TCHAR*, INT64*> key_int;
		key_int[_T("id")] = &m_id;
		for (std::hash_multimap<TCHAR*, INT64*>::iterator it = key_int.begin(); it != key_int.end(); it++) {
			if (!jval.at(it->first).is_null()) {
				*it->second = jval.at(it->first).as_number().to_int64();
			}
		}

		std::hash_map<TCHAR*, CString*> key_cstr;
		key_cstr[_T("name")] = &m_name;
		for (std::hash_multimap<TCHAR*, CString*>::iterator it = key_cstr.begin(); it != key_cstr.end(); it++) {
			if (!jval.at(it->first).is_null()) {
				*it->second = jval.at(it->first).as_string().c_str();
			}
		}

		json::value arrayObj = jval[_T("variants")];
		int size = arrayObj.size();
		for (int i = 0; i < size; i++) {  
			AbTestVariants abVarients;
			abVarients.DataParse(arrayObj[i]);
			m_abTestVariants.push_back(abVarients);
		}
	}
};