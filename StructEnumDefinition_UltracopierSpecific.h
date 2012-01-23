/** \file StructEnumDefinition_UltracopierSpecific.h
\brief Define the structure and enumeration used in ultracopier only
\author alpha_one_x86
\version 0.3
\date 2010 */

#include <QString>
#include <QList>
#include <QDomElement>

#ifndef STRUCTDEF_ULTRACOPIERSPECIFIC_H
#define STRUCTDEF_ULTRACOPIERSPECIFIC_H

enum PluginType
{
	PluginType_Unknow,
	PluginType_CopyEngine,
	PluginType_Languages,
	PluginType_Listener,
	PluginType_PluginLoader,
	PluginType_SessionLoader,
	PluginType_Themes
};

struct PluginsAvailable
{
	PluginType category;
	QString path;
	QString name;
	QString writablePath;
	QDomElement categorySpecific;
	QString version;
	QList<QStringList> informations;
	QString errorString;
	bool isWritable;
	bool isAuth;
};

enum DebugLevel_custom
{
	DebugLevel_custom_Information,
	DebugLevel_custom_Critical,
	DebugLevel_custom_Warning,
	DebugLevel_custom_Notice,
	DebugLevel_custom_UserNote
};

#endif // STRUCTDEF_ULTRACOPIERSPECIFIC_H