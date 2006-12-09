//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: muuli.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_muuli_H__
#define __WDR_muuli_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "muuli_wdr.h"
#endif

// Include wxWidgets' headers

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/image.h>
#include <wx/statline.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/toolbar.h>
#include <wx/tglbtn.h>

// Declare window functions

extern wxSizer *s_dlgcnt;
extern wxSizer *contentSizer;
extern wxSizer *s_fed2klh;
const int ID_TEXT = 10000;
const int ID_TEXTCTRL = 10001;
const int ID_BUTTON_FAST = 10002;
const int IDC_SHOWSTATUSTEXT = 10003;
const int ID_LINE = 10004;
const int ID_STATICBITMAP = 10005;
wxSizer *muleDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_SRV_SPLITTER = 10006;
wxSizer *serverListDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *s_searchdlgsizer;
extern wxSizer *s_searchsizer;
const int IDC_SEARCHNAME = 10007;
const int ID_SEARCHTYPE = 10008;
const int IDC_EXTENDEDSEARCHCHECK = 10009;
const int IDC_FILTERCHECK = 10010;
extern wxSizer *s_extendedsizer;
const int IDC_TypeSearch = 10011;
const int ID_AUTOCATASSIGN = 10012;
const int IDC_EDITSEARCHEXTENSION = 10013;
const int IDC_SPINSEARCHMIN = 10014;
const int IDC_SEARCHMINSIZE = 10015;
const int IDC_SPINSEARCHMAX = 10016;
const int IDC_SEARCHMAXSIZE = 10017;
const int IDC_SPINSEARCHAVAIBILITY = 10018;
extern wxSizer *s_filtersizer;
const int ID_FILTER_TEXT = 10019;
const int ID_FILTER = 10020;
const int ID_FILTER_INVERT = 10021;
const int ID_FILTER_KNOWN = 10022;
const int IDC_STARTS = 10023;
const int IDC_SEARCHMORE = 10024;
const int IDC_CANCELS = 10025;
const int IDC_SDOWNLOAD = 10026;
const int IDC_SEARCH_RESET = 10027;
const int IDC_CLEAR_RESULTS = 10028;
const int ID_NOTEBOOK = 10029;
const int ID_SEARCHPROGRESS = 10030;
wxSizer *searchDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *transfer_top_boxsizer;
const int ID_BTNCLRCOMPL = 10031;
const int ID_CATEGORIES = 10032;
const int ID_DLOADLIST = 10033;
wxSizer *transferTopPane( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *queueSizer;
extern wxSizer *s_clientlistHeader;
const int ID_CLIENTTOGGLE = 10034;
const int ID_BTNSWITCHUP = 10035;
const int ID_CLIENTCOUNT = 10036;
const int ID_CLIENTLIST = 10037;
wxSizer *transferBottomPane( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_FRIENDLIST = 10038;
const int IDC_CHATSELECTOR = 10039;
const int IDC_CMESSAGE = 10040;
const int IDC_CSEND = 10041;
const int IDC_CCLOSE = 10042;
wxSizer *messagePage( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *IDC_FD_X0;
const int IDC_FD_X1 = 10043;
const int IDC_FNAME = 10044;
const int IDC_FD_X2 = 10045;
const int IDC_METFILE = 10046;
const int IDC_FD_X3 = 10047;
const int IDC_FHASH = 10048;
const int IDC_FD_X4 = 10049;
const int IDC_FSIZE = 10050;
const int IDC_FD_X5 = 10051;
const int IDC_PFSTATUS = 10052;
const int IDC_FD_X15 = 10053;
const int IDC_LASTSEENCOMPL = 10054;
extern wxSizer *IDC_FD_X6;
const int IDC_FD_X7 = 10055;
const int IDC_SOURCECOUNT = 10056;
const int IDC_FD_X10 = 10057;
const int IDC_SOURCECOUNT2 = 10058;
const int IDC_FD_X9 = 10059;
const int IDC_PARTCOUNT = 10060;
const int IDC_FD_X11 = 10061;
const int IDC_PARTAVAILABLE = 10062;
const int IDC_FD_X13 = 10063;
const int IDC_DATARATE = 10064;
const int IDC_DLACTIVETIME = 10065;
const int IDC_FD_X14 = 10066;
const int IDC_TRANSFERED = 10067;
const int IDC_FD_X12 = 10068;
const int IDC_COMPLSIZE = 10069;
const int IDC_PROCCOMPL = 10070;
extern wxSizer *IDC_FD_ICH;
const int IDC_FD_LSTATS1 = 10071;
const int IDC_FD_STATS1 = 10072;
const int IDC_FD_LSTATS2 = 10073;
const int IDC_FD_STATS2 = 10074;
const int IDC_FD_LSTATS3 = 10075;
const int IDC_FD_STATS3 = 10076;
const int IDC_LISTCTRLFILENAMES = 10077;
const int IDC_TAKEOVER = 10078;
const int IDC_CMTBT = 10079;
const int IDC_BUTTONSTRIP = 10080;
const int IDC_FILENAME = 10081;
const int IDC_APPLY = 10082;
const int IDC_APPLY_AND_CLOSE = 10083;
const int ID_CLOSEWNDFD = 5100;
wxSizer *fileDetails( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_CMT_TEXT = 10084;
const int IDC_FC_CLEAR = 10085;
const int IDC_RATELIST = 10086;
const int IDCOK = 10087;
const int IDCCANCEL = 10088;
wxSizer *commentDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_LST = 10089;
const int IDC_CMSTATUS = 10090;
const int IDCREF = 10091;
wxSizer *commentLstDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_ANIMATE = 10092;
const int ID_HTTPDOWNLOADPROGRESS = 10093;
const int IDC_DOWNLOADSIZE = 10094;
const int ID_HTTPCANCEL = 5101;
wxSizer *downloadDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_IPADDRESS = 10095;
const int ID_IPORT = 10096;
const int ID_USERNAME = 10097;
const int ID_USERHASH = 10098;
const int ID_ADDFRIEND = 10099;
const int ID_CLOSEDLG = 10100;
wxSizer *addFriendDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_BTNRELSHARED = 10101;
const int ID_SHFILELIST = 10102;
const int IDC_SREQUESTED = 10103;
const int ID_GAUGE = 10104;
const int IDC_SREQUESTED2 = 10105;
const int IDC_SACCEPTED = 10106;
const int IDC_SACCEPTED2 = 10107;
const int IDC_STRANSFERED = 10108;
const int IDC_STRANSFERED2 = 10109;
wxSizer *sharedfilesDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *testSizer;
const int ID_DLOADSCOPE = 10110;
const int IDC_C0 = 10111;
const int IDC_C0_3 = 10112;
const int IDC_C0_2 = 10113;
const int ID_ULOADSCOPE = 10114;
const int IDC_C1 = 10115;
const int IDC_C1_3 = 10116;
const int IDC_C1_2 = 10117;
const int ID_OTHERS = 10118;
const int IDC_S3 = 10119;
const int IDC_S0 = 10120;
const int ID_ACTIVEC = 10121;
const int IDC_S1 = 10122;
const int ID_TREECTRL = 10123;
wxSizer *statsDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_DNAME = 10124;
const int ID_DHASH = 10125;
const int ID_DSOFT = 10126;
const int ID_DVERSION = 10127;
const int ID_DIP = 10128;
const int ID_DID = 10129;
const int ID_DSIP = 10130;
const int ID_DSNAME = 10131;
const int ID_DDOWNLOADING = 10132;
const int ID_DAVDR = 10133;
const int ID_DAVUR = 10134;
const int ID_DDOWN = 10135;
const int ID_DDUP = 10136;
const int ID_DDOWNTOTAL = 10137;
const int ID_DUPTOTAL = 10138;
const int ID_DRATIO = 10139;
const int IDC_CDIDENT = 10140;
const int ID_DRATING = 10141;
const int ID_DSCORE = 10142;
const int ID_CLOSEWND = 10143;
wxSizer *clientDetails( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_NICK = 10144;
const int IDC_LANGUAGE = 10145;
extern wxSizer *IDC_MISC_OPTIONS;
const int IDC_NEWVERSION = 10146;
const int IDC_STARTMIN = 10147;
const int IDC_EXIT = 10148;
const int IDC_ENABLETRAYICON = 10149;
const int IDC_MINTRAY = 10150;
const int IDC_TOOLTIPDELAY_LBL = 10151;
const int IDC_TOOLTIPDELAY = 10152;
const int IDC_BROWSER = 10153;
const int ID_CUSTOMBROWSETEXT = 10154;
const int IDC_BROWSERSELF = 10155;
const int IDC_SELBROWSER = 10156;
const int IDC_BROWSERTABS = 10157;
wxSizer *PreferencesGeneralTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_DLIMIT_LBL = 10158;
const int IDC_MAXDOWN = 10159;
const int IDC_KBS1 = 10160;
const int IDC_ULIMIT_LBL = 10161;
const int IDC_MAXUP = 10162;
const int IDC_KBS4 = 10163;
const int IDC_SLOTALLOC = 10164;
const int IDC_DCAP_LBL = 10165;
const int IDC_DOWNLOAD_CAP = 10166;
const int IDC_KBS2 = 10167;
const int IDC_UCAP_LBL = 10168;
const int IDC_UPLOAD_CAP = 10169;
const int IDC_KBS3 = 10170;
const int IDC_PORT = 10171;
const int IDC_UDPPORT = 10172;
const int IDC_UDPDISABLE = 10173;
const int IDC_ADDRESS = 10174;
const int ID_TEXT_CLIENT_UDP_PORT = 10175;
const int IDC_MAXSRCHARD_LBL = 10176;
const int IDC_MAXSOURCEPERFILE = 10177;
const int IDC_MAXCONLABEL = 10178;
const int IDC_MAXCON = 10179;
const int IDC_NETWORKED2K = 10180;
const int IDC_NETWORKKAD = 10181;
const int IDC_UPNP_ENABLED = 10182;
const int IDC_UPNPTCPPORT = 10183;
const int IDC_AUTOCONNECT = 10184;
const int IDC_RECONN = 10185;
const int IDC_SHOWOVERHEAD = 10186;
wxSizer *PreferencesConnectionTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_REMOVEDEAD = 10187;
const int IDC_SERVERRETRIES = 10188;
const int IDC_RETRIES_LBL = 10189;
const int IDC_AUTOSERVER = 10190;
const int IDC_EDITADR = 10191;
const int IDC_UPDATESERVERCONNECT = 10192;
const int IDC_UPDATESERVERCLIENT = 10193;
const int IDC_SCORE = 10194;
const int IDC_SMARTIDCHECK = 10195;
const int IDC_SAFESERVERCONNECT = 10196;
const int IDC_AUTOCONNECTSTATICONLY = 10197;
const int IDC_MANUALSERVERHIGHPRIO = 10198;
wxSizer *PreferencesServerTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_ICH = 10199;
const int IDC_AICHTRUST = 10200;
const int IDC_ADDNEWFILESPAUSED = 10201;
const int IDC_DAP = 10202;
const int IDC_PREVIEWPRIO = 10203;
const int IDC_UAP = 10204;
const int IDC_FULLCHUNKTRANS = 10205;
const int IDC_STARTNEXTFILE = 10206;
const int IDC_STARTNEXTFILE_SAME = 10207;
const int IDC_SRCSEEDS = 10208;
const int IDC_CHECKDISKSPACE = 10209;
const int ID_MINDISKTEXT = 10210;
const int IDC_MINDISKSPACE = 10211;
wxSizer *PreferencesFilesTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_INCFILES = 10212;
const int IDC_SELINCDIR = 10213;
const int IDC_TEMPFILES = 10214;
const int IDC_SELTEMPDIR = 10215;
const int IDC_SHARESELECTOR = 10216;
const int IDC_SHAREHIDDENFILES = 10217;
const int IDC_VIDEOPLAYER = 10218;
const int IDC_BROWSEV = 10219;
const int IDC_VIDEOBACKUP = 10220;
wxSizer *PreferencesDirectoriesTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_SLIDERINFO = 10221;
const int IDC_SLIDER = 10222;
const int IDC_SLIDERINFO3 = 10223;
const int IDC_SLIDER3 = 10224;
const int IDC_SLIDERINFO4 = 10225;
const int IDC_SLIDER4 = 10226;
const int IDC_PREFCOLORS = 10227;
const int IDC_COLORSELECTOR = 10228;
const int IDC_COLOR_BUTTON = 10229;
const int IDC_SLIDERINFO2 = 10230;
const int IDC_SLIDER2 = 10231;
const int IDC_CLIENTVERSIONS = 10232;
wxSizer *PreferencesStatisticsTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_CB_TBN_USESOUND = 10233;
const int IDC_EDIT_TBN_WAVFILE = 10234;
const int IDC_BTN_BROWSE_WAV = 10235;
const int IDC_CB_TBN_ONLOG = 10236;
const int IDC_CB_TBN_ONCHAT = 10237;
const int IDC_CB_TBN_POP_ALWAYS = 10238;
const int IDC_CB_TBN_ONDOWNLOAD = 10239;
const int IDC_CB_TBN_ONNEWVERSION = 10240;
const int IDC_CB_TBN_IMPORTATNT = 10241;
const int IDC_SENDMAIL = 10242;
const int IDC_SMTP = 10243;
const int IDC_EMAIL = 10244;
wxSizer *PreferencesNotifyTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_WARNING = 10245;
const int IDC_STATIC = 10246;
const int IDC_MAXCON5SECLABEL = 10247;
const int IDC_MAXCON5SEC = 10248;
const int IDC_FILEBUFFERSIZE_STATIC = 10249;
const int IDC_FILEBUFFERSIZE = 10250;
const int IDC_QUEUESIZE_STATIC = 10251;
const int IDC_QUEUESIZE = 10252;
const int IDC_SERVERKEEPALIVE_LABEL = 10253;
const int IDC_SERVERKEEPALIVE = 10254;
wxSizer *PreferencesaMuleTweaksTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_PERCENT = 10255;
const int IDC_PROGBAR = 10256;
const int IDC_3DDEP = 10257;
const int IDC_3DDEPTH = 10258;
const int IDC_FLAT = 10259;
const int IDC_ROUND = 10260;
const int IDC_USESKIN = 10261;
const int IDC_SKINFILE = 10262;
const int IDC_SELSKINFILE = 10263;
const int IDC_AUTOSORT = 10264;
const int IDC_FED2KLH = 10265;
const int IDC_EXTCATINFO = 10266;
const int IDC_SHOWRATEONTITLE = 10267;
const int IDC_VERTTOOLBAR = 10268;
wxSizer *PreferencesGuiTweaksTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_NNS_HANDLING = 10269;
const int IDC_ENABLE_AUTO_FQS = 10270;
const int IDC_ENABLE_AUTO_HQRS = 10271;
const int IDC_HQR_VALUE = 10272;
const int IDC_AUTO_DROP_TIMER = 10273;
wxSizer *PreferencesSourcesDroppingTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_ENABLE_WEB = 10274;
const int IDC_WEB_PORT = 10275;
const int IDC_UPNP_WEBSERVER_ENABLED = 10276;
const int IDC_WEB_REFRESH_TIMEOUT = 10277;
const int IDC_WEB_GZIP = 10278;
const int IDC_ENABLE_WEB_LOW = 10279;
const int IDC_WEB_PASSWD = 10280;
const int IDC_WEB_PASSWD_LOW = 10281;
const int IDC_WEBTEMPLATE = 10282;
const int IDC_EXT_CONN_ACCEPT = 10283;
const int IDC_EXT_CONN_IP = 10284;
const int IDC_EXT_CONN_TCP_PORT = 10285;
const int IDC_UPNP_EC_ENABLED = 10286;
const int IDC_EXT_CONN_PASSWD = 10287;
wxSizer *PreferencesRemoteControlsTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *prefs_main_sizer;
extern wxSizer *prefs_sizer;
const int ID_PREFSLISTCTRL = 10288;
const int ID_PREFS_OK_TOP = 10289;
const int ID_PREFS_CANCEL_TOP = 10290;
wxSizer *preferencesDlgTop( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_STATIC_TITLE = 10291;
const int IDC_TITLE = 10292;
const int IDC_STATIC_COMMENT = 10293;
const int IDC_COMMENT = 10294;
const int IDC_STATIC_INCOMING = 10295;
const int IDC_INCOMING = 10296;
const int IDC_BROWSE = 10297;
const int IDC_STATIC_PRIO = 10298;
const int IDC_PRIOCOMBO = 10299;
const int IDC_STATIC_COLOR = 10300;
const int ID_BOX_CATCOLOR = 10301;
const int IDC_CATCOLOR = 10302;
wxSizer *CategoriesEditWindow( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_SPLATTER = 10303;
wxSizer *transferDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_SERVERINFO = 10304;
const int ID_BTN_RESET_SERVER = 10305;
wxSizer *ServerInfoLog( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LOGVIEW = 10306;
const int ID_BTN_RESET = 10307;
wxSizer *aMuleLog( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_UPDATELIST = 10308;
const int IDC_SERVERLISTURL = 10309;
const int IDC_SERVERNAME = 10310;
const int IDC_IPADDRESS = 10311;
const int IDC_SPORT = 10312;
const int ID_ADDTOLIST = 10313;
const int IDC_ED2KDISCONNECT = 10314;
const int ID_SERVERLIST = 10315;
wxSizer *serverListDlgUp( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_SRVLOG_NOTEBOOK = 10316;
wxSizer *serverListDlgDown( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LOCALETEXT = 10317;
const int ID_OK = 10318;
const int ID_LOCALENEVERAGAIN = 10319;
wxSizer *LocaleWarning( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *kadSizer;
const int ID_UPDATEKADLIST = 10320;
const int IDC_NODESLISTURL = 10321;
const int ID_KADSCOPE = 10322;
const int ID_NODE_IP1 = 10323;
const int ID_NODE_IP2 = 10324;
const int ID_NODE_IP3 = 10325;
const int ID_NODE_IP4 = 10326;
const int ID_NODE_PORT = 10327;
const int ID_NODECONNECT = 10328;
const int ID_KNOWNNODECONNECT = 10329;
const int ID_KADDISCONNECT = 10330;
wxSizer *KadDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_STATICTEXT = 10331;
const int ID_ED2KINFO = 10332;
wxSizer *ED2K_Info( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_SEESHARES = 10333;
const int IDC_IPFCLIENTS = 10334;
const int IDC_IPFSERVERS = 10335;
const int IDC_IPFRELOAD = 10336;
const int IDC_IPFILTERURL = 10337;
const int IDC_IPFILTERUPDATE = 10338;
const int IDC_AUTOIPFILTER = 10339;
const int ID_IPFILTERLEVEL = 10340;
const int IDC_FILTERLAN = 10341;
const int IDC_PARANOID = 10342;
const int IDC_SECIDENT = 10343;
wxSizer *PreferencesSecurityTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_ONLINESIG = 10344;
const int IDC_OSUPDATE = 10345;
const int IDC_OSDIR = 10346;
const int IDC_SELOSDIR = 10347;
wxSizer *PreferencesOnlineSigTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_MSGFILTER = 10348;
const int IDC_MSGFILTER_ALL = 10349;
const int IDC_MSGFILTER_NONFRIENDS = 10350;
const int IDC_MSGFILTER_NONSECURE = 10351;
const int IDC_MSGFILTER_WORD = 10352;
const int IDC_MSGWORD = 10353;
wxSizer *PreferencesMessagesTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_PROXY_ENABLE_PROXY = 10354;
const int ID_PROXY_TYPE = 10355;
const int ID_PROXY_NAME = 10356;
const int ID_PROXY_PORT = 10357;
const int ID_PROXY_ENABLE_PASSWORD = 10358;
const int ID_PROXY_USER = 10359;
const int ID_PROXY_PASSWORD = 10360;
const int ID_PROXY_AUTO_SERVER_CONNECT_WITHOUT_PROXY = 10361;
wxSizer *PreferencesProxyTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_REMOTE_HOST = 10362;
const int ID_REMOTE_PORT = 10363;
const int ID_EC_LOGIN = 10364;
const int ID_EC_PASSWD = 10365;
const int ID_EC_SAVE = 10366;
wxSizer *CoreConnect( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_VERBOSEDEBUG = 10367;
const int ID_DEBUGCATS = 10368;
wxSizer *PreferencesDebug( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *IDC_CURJOB;
const int IDC_CONV_PB_LABEL = 10369;
const int IDC_CONV_PROZENT = 10370;
const int IDC_CONV_PB_CURRENT = 10371;
const int IDC_JOBLIST = 10372;
const int IDC_ADDITEM = 10373;
const int IDC_RETRY = 10374;
const int IDC_CONVREMOVE = 10375;
wxSizer *convertDlg( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_STATICETXT = 10376;
const int ID_KADINFO = 10377;
wxSizer *Kad_Info( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *netSizer;
const int ID_NETNOTEBOOK = 10378;
wxSizer *NetDialog( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *IDC_PREFS_EVENTS_PAGE;
const int IDC_EVENTLIST = 10379;
wxSizer *PreferencesEventsTab( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

const int ID_BUTTONCONNECT = 10380;
const int ID_BUTTONNETWORKS = 10381;
const int ID_BUTTONSEARCH = 10382;
const int ID_BUTTONTRANSFER = 10383;
const int ID_BUTTONSHARED = 10384;
const int ID_BUTTONMESSAGES = 10385;
const int ID_BUTTONSTATISTICS = 10386;
const int ID_BUTTONNEWPREFERENCES = 10387;
const int ID_BUTTONIMPORT = 10388;
const int ID_ABOUT = 10389;
void muleToolbar( wxToolBar *parent );

// Declare bitmap functions

wxBitmap clientImages( size_t index );

wxBitmap dlStatusImages( size_t index );

wxBitmap connImages( size_t index );

wxBitmap moreImages( size_t index );

wxBitmap amuleSpecial( size_t index );

wxBitmap connButImg( size_t index );

wxBitmap amuleDlgImages( size_t index );

#endif

// End of generated file
