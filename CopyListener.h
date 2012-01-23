/** \file CopyListener.h
\brief Define the class to load the plugin and lunch it
\author alpha_one_x86
\version 0.3
\date 2010 */ 

#ifndef COPYLISTENER_H
#define COPYLISTENER_H

#include <QObject>
#include <QList>
#include <QPluginLoader>

#include "interface/PluginInterface_Listener.h"
#include "Environment.h"
#include "GlobalClass.h"
#include "PluginLoader.h"

/** \brief to load all the listener and parse all event */
class CopyListener : public QObject, public GlobalClass
{
	Q_OBJECT
	public:
		explicit CopyListener(QObject *parent = 0);
		~CopyListener();
		/** \brief send of one listener is loaded */
		bool oneListenerIsLoaded();
		/** \brief to resend the state */
		void resendState();
	private slots:
		//void newPlugin();
		void newPluginCopy(quint32 orderId,QStringList sources);
		void newPluginCopy(quint32 orderId,QStringList sources,QString destination);
		void newPluginMove(quint32 orderId,QStringList sources);
		void newPluginMove(quint32 orderId,QStringList sources,QString destination);
		void onePluginAdded(PluginsAvailable plugin);
		void onePluginWillBeRemoved(PluginsAvailable plugin);
		void newState(ListeningState state);
		#ifdef ULTRACOPIER_DEBUG
		void debugInformation(DebugLevel level,const QString& fonction,const QString& text,const QString& file,const int& ligne);
		#endif // ULTRACOPIER_DEBUG
		void allPluginIsloaded();
	public slots:
		/** \brief the copy is finished
		 \param orderId id used when it have send the copy
		 \param withError true if it have found error
		 \see newCopy()
		 \see newMove()
		*/
		void copyFinished(const quint32 & orderId,bool withError);
		/** \brief the copy is canceled by the user
		 \param orderId id used when it have send the copy
		 \see newCopy()
		 \see newMove()
		*/
		void copyCanceled(const quint32 & orderId);
		/** \brief try listen, to get copy/move from external source (mainly the file manager)
		 \see close()
		*/
		void listen();
		/** \brief stop listen, to get copy/move from external source (mainly the file manager)
		 \see listen()
		*/
		void close();
	signals:
		void newCopy(quint32 orderId,QStringList protocolsUsedForTheSources,QStringList sources);
		void newCopy(quint32 orderId,QStringList protocolsUsedForTheSources,QStringList sources,QString protocolsUsedForTheDestination,QString destination);
		void newMove(quint32 orderId,QStringList protocolsUsedForTheSources,QStringList sources);
		void newMove(quint32 orderId,QStringList protocolsUsedForTheSources,QStringList sources,QString protocolsUsedForTheDestination,QString destination);
		void listenerReady(ListeningState state,bool havePlugin,bool someAreInWaitOfReply);
		void pluginLoaderReady(CatchState state,bool havePlugin,bool someAreInWaitOfReply);
	private:
		struct PluginListener
		{
			PluginInterface_Listen *listenInterface;
			QPluginLoader *pluginLoader;
			QString path;
			ListeningState state;
			bool inWaitOfReply;
			LocalPluginOptions *options;
		};
		typedef struct PluginListener PluginListener;
		QList<PluginListener> pluginList;
		//for the options
		quint32 nextOrderId;
		QList<quint32> orderList;
		//for the copy as suspend
		struct CopyRunning
		{
			PluginInterface_Listen *listenInterface;
			quint32 pluginOrderId;
			quint32 orderId;
		};
		typedef struct CopyRunning CopyRunning;
		QList<CopyRunning> copyRunningList;
		quint32 incrementOrderId();
		bool tryListen;
		PluginLoader pluginLoader;
		ListeningState last_state;
		bool last_have_plugin,last_inWaitOfReply;
		void sendState(bool force=false);
};

#endif // COPYLISTENER_H