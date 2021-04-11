/*!
 * @file
 * @brief System-wide ERD definitions.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef SYSTEMERDS_H
#define SYSTEMERDS_H

#include "WiFiData.h"
#include "WiFiNetworkStatusUpdate.h"
#include "ApplicationVersionCharacters.h"
#include "ParametricVersionCharacters.h"
#include "Timer.h"
#include "I_Uart.h"
#include "GitHash.h"
#include "I_ContextProtector.h"
#include "Signal.h"
#include "I_Gea2MessageEndpoint.h"
#include "I_Action.h"
#include "CookEngineStatus.h"
#include "Temperature.h"
#include "FaultResultBits.h"
#include "XMacroUtils.h"
#include "ApplianceType.h"
#include "WiFiNetworkState.h"
#include "WiFiTypes.h"
#include "FaultHandler.h"
#include "FaultErdExpansions.h"
#include "ServiceDiagnosticsRevision3.h"
#include "RemoteErdConvertedCallbacks.h"
#include "BundledSettings.h"
#include "HeatingElements.h"
#include "OvenLightRequest.h"
#include "DoorLockRequests.h"
#include "DoorPositions.h"
#include "ConvectionFanState.h"
#include "TimeInMinutes.h"
#include "CountDownTime.h"
#include "DoorLockStatuses.h"
#include "CavityConfiguration.h"
#include "RecipeDownloadStatus.h"
#include "RecipeStatus.h"
#include "RemoteOvenConfiguration.h"
#include "DisplaySettings.h"
#include "CookingSettings.h"
#include "Loads.h"
#include "WiFiTypes.h"
#include "Version.h"
#include "WiFiService.h"
#include "Ota.h"
#include "LcdUiConfiguration.h"

#ifndef ENDIANNESS_FREE
#define ENDIANNESS_FREE false
#endif

#ifndef ENDIANNESS_SWAP
#define ENDIANNESS_SWAP true
#endif

#define IO_None 0
#define IO_O 1
#define IO_All 2

#define RamErd 0
#define NvErd 1
#define NoDefaultValue 0

#define INCLUDE_STORE_IN_RAM_0(_x) _x
//TODO This is a hack since we don't have NVRAM storage yet.  Everything will be in RAM
#define INCLUDE_STORE_IN_RAM_1(_x) _x
#define INCLUDE_STORE_IN_RAM_2(_x)

#define INCLUDE_STORE_IN_NVRAM_0(_x)
#define INCLUDE_STORE_IN_NVRAM_1(_x)
#define INCLUDE_STORE_IN_NVRAM_2(_x)

#define INCLUDE_INPUT_OUTPUT_0(_x)
#define INCLUDE_INPUT_OUTPUT_1(_x)
#define INCLUDE_INPUT_OUTPUT_2(_x) _x

#define INCLUDE_OUTPUT_0(_x)
#define INCLUDE_OUTPUT_1(_x) _x
#define INCLUDE_OUTPUT_2(_x) _x

typedef uint8_t ModelNumber_t[32];
typedef uint8_t SerialNumber_t[32];
typedef uint8_t LcdOtaModel_t[64];

//    ERD NAME                                                           ERD #      TYPE                                                  ENDIANNESS         IO          STORAGE  DefaultValue
#define ERD_TABLE(ENTRY)  \
   ENTRY(Erd_ApplianceModel,                                             0x0001,    ModelNumber_t,                                        ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ApplianceSerial,                                            0x0002,    SerialNumber_t,                                       ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ApplianceType,                                              0x0008,    ApplianceType_t,                                      ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_BuildNumber,                                                0x0031,    uint32_t,                                             ENDIANNESS_SWAP,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ResetApplianceToMc,                                         0x0032,    bool,                                                 ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_GitHash,                                                    0x007F,    GitHash_t,                                            ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ServiceDiagnosticsApiVersion,                               0x008F,    ServiceDiagnosticsApiVersion_t,                       ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ServiceDiagnosticsRevision3Manifest,                        0x0090,    ServiceDiagnosticsRevision3Manifest_t,                ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_LcdApplicationVersion,                                      0x0106,    LcdCurrentVersion_t,                                  ENDIANNESS_FREE,   IO_All,     RamErd,  RamErd                         ) \
   ENTRY(Erd_LcdAvailableVersion,                                        0x0107,    LcdAvailableVersion_t,                                ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CurrentUpgradeStatus,                                       0x0108,    uint8_t,                                              ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_ApplicationVersion,                                         0x0300,    ApplicationVersionCharacters_t,                       ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ParametricVersion,                                          0x0301,    ParametricVersionCharacters_t,                        ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_PendingSelfCleanCancelSignal,                               0x0311,    Signal_t,                                             ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_OvenLightRequest,                                           0x0312,    OvenLightRequest_t,                                   ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ResetAppliance,                                             0x0313,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_DelayTimeRemainingMinutes_Cavity1,                          0x5102,    TimeInMinutes_t,                                      ENDIANNESS_SWAP,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_OvenCavity1_ProbeTemperature,                               0x5103,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CookTimeRemainingMinutes_Cavity1,                           0x5104,    TimeInMinutes_t,                                      ENDIANNESS_SWAP,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DisplayTimer_Cavity1_Remote,                                0x5105,    TimeInMinutes_t,                                      ENDIANNESS_SWAP,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ProbePresence_Cavity1,                                      0x5107,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ElapsedCookTimeMinutes_Cavity1,                             0x5108,    TimeInMinutes_t,                                      ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DisplayTemperature_Cavity1,                                 0x5109,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_OvenCavity1_ResolvedTemperature,                            0x510D,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RTDTemperature_Cavity1,                                     0x510E,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_OvenCavity1_ProbeDisplayTemperature,                        0x510F,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_DelayTimeRemainingMinutes_Cavity2,                          0x5202,    TimeInMinutes_t,                                      ENDIANNESS_SWAP,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_OvenCavity2_ProbeTemperature,                               0x5203,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CookTimeRemainingMinutes_Cavity2,                           0x5204,    TimeInMinutes_t,                                      ENDIANNESS_SWAP,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DisplayTimer_Cavity2_Remote,                                0x5205,    TimeInMinutes_t,                                      ENDIANNESS_SWAP,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ProbePresence_Cavity2,                                      0x5207,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ElapsedCookTimeMinutes_Cavity2,                             0x5208,    TimeInMinutes_t,                                      ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DisplayTemperature_Cavity2,                                 0x5209,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_OvenCavity2_ResolvedTemperature,                            0x520D,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RTDTemperature_Cavity2,                                     0x520E,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_OvenCavity2_ProbeDisplayTemperature,                        0x520F,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_WiFiMacAddress,                                             0x6000,    WiFiMacAddress_t,                                     ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WiFiApSsid,                                                 0x6001,    WiFiNetworkName_t,                                    ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WiFiApPassphrase,                                           0x6002,    WiFiPassword_t,                                       ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WiFiNetworkStatus,                                          0x6003,    WiFiNetworkState_t,                                   ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ConnectedSsid,                                              0x6027,    WiFiNetworkName_t,                                    ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ConnectedPassphrase,                                        0x6028,    WiFiPassword_t,                                       ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_LinuxLcdOtaModel,                                           0x6029,    LcdOtaModel_t,                                        ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_HeartbeatRequestDelayTime,                                  0x6300,    uint8_t,                                              ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_FieldOrProdV2ServerEndpoint,                                0x6301,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_PrimaryOvenDiagnosticsEntityLocation,                       0xE000,    Erd_t,                                                ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsEntityLocation,                     0xE001,    Erd_t,                                                ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_LcdUiDiagnosticsEntityLocation,                             0xE002,    Erd_t,                                                ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_FaultBitmap,                                                0xE010,    FaultBitmap_t,                                        ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_FaultBitmapFromPrimaryMc,                                   0xE011,    FaultBitmap_t,                                        ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_FaultBitmapFromSecondayMc,                                  0xE012,    FaultBitmap_t,                                        ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_FaultBitmapFromSingularMc,                                  0xE013,    FaultBitmap_t,                                        ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_PrimaryOvenDiagnosticsEntityManifest,                       0xE100,    ServiceDiagnosticsRevision3EntityManifest_t,          ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsEntityCycleCount,                     0xE101,    uint32_t,                                             ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsEntityRunTimeMinutes,                 0xE102,    uint32_t,                                             ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableStatus,                     0xE103,    ServiceDiagnosticsRevision3TableStatus_t,             ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableClear,                      0xE104,    ServiceDiagnosticsRevision3TableClearRequest_t,       ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableEntry0,                     0xE105,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableEntry1,                     0xE106,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableEntry2,                     0xE107,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableEntry3,                     0xE108,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableEntry4,                     0xE109,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableEntry5,                     0xE10A,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableEntry6,                     0xE10B,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableEntry7,                     0xE10C,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableEntry8,                     0xE10D,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableEntry9,                     0xE10E,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceStatus,                  0xE10F,    ServiceDiagnosticsRevision3SequenceStatus_t,          ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceClear,                   0xE110,    ServiceDiagnosticsRevision3SequenceClearRequest_t,    ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceEntry0,                  0xE111,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceEntry1,                  0xE112,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceEntry2,                  0xE113,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceEntry3,                  0xE114,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceEntry4,                  0xE115,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceEntry5,                  0xE116,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceEntry6,                  0xE117,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceEntry7,                  0xE118,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceEntry8,                  0xE119,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultSequenceEntry9,                  0xE11A,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   \
   ENTRY(Erd_SecondaryOvenDiagnosticsEntityManifest,                     0xE200,    ServiceDiagnosticsRevision3EntityManifest_t,          ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsEntityCycleCount,                   0xE201,    uint32_t,                                             ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsEntityRunTimeMinutes,               0xE202,    uint32_t,                                             ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableStatus,                   0xE203,    ServiceDiagnosticsRevision3TableStatus_t,             ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableClear,                    0xE204,    ServiceDiagnosticsRevision3TableClearRequest_t,       ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableEntry0,                   0xE205,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableEntry1,                   0xE206,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableEntry2,                   0xE207,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableEntry3,                   0xE208,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableEntry4,                   0xE209,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableEntry5,                   0xE20A,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableEntry6,                   0xE20B,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableEntry7,                   0xE20C,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableEntry8,                   0xE20D,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableEntry9,                   0xE20E,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceStatus,                0xE20F,    ServiceDiagnosticsRevision3SequenceStatus_t,          ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceClear,                 0xE210,    ServiceDiagnosticsRevision3SequenceClearRequest_t,    ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceEntry0,                0xE211,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceEntry1,                0xE212,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceEntry2,                0xE213,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceEntry3,                0xE214,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceEntry4,                0xE215,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceEntry5,                0xE216,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceEntry6,                0xE217,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceEntry7,                0xE218,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceEntry8,                0xE219,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultSequenceEntry9,                0xE21A,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   \
   ENTRY(Erd_LcdUiDiagnosticsEntityManifest,                             0xE300,    ServiceDiagnosticsRevision3EntityManifest_t,          ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_LcdUiDiagnosticsEntityCycleCount,                           0xE301,    uint32_t,                                             ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsEntityRunTimeMinutes,                       0xE302,    uint32_t,                                             ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableStatus,                           0xE303,    ServiceDiagnosticsRevision3TableStatus_t,             ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableClear,                            0xE304,    ServiceDiagnosticsRevision3TableClearRequest_t,       ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableEntry0,                           0xE305,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableEntry1,                           0xE306,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableEntry2,                           0xE307,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableEntry3,                           0xE308,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableEntry4,                           0xE309,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableEntry5,                           0xE30A,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableEntry6,                           0xE30B,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableEntry7,                           0xE30C,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableEntry8,                           0xE30D,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultTableEntry9,                           0xE30E,    ServiceDiagnosticsRevision3FaultTableEntry_t,         ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceStatus,                        0xE30F,    ServiceDiagnosticsRevision3SequenceStatus_t,          ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceClear,                         0xE310,    ServiceDiagnosticsRevision3SequenceClearRequest_t,    ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceEntry0,                        0xE311,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceEntry1,                        0xE312,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceEntry2,                        0xE313,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceEntry3,                        0xE314,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceEntry4,                        0xE315,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceEntry5,                        0xE316,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceEntry6,                        0xE317,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceEntry7,                        0xE318,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceEntry8,                        0xE319,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_LcdUiDiagnosticsFaultSequenceEntry9,                        0xE31A,    ServiceDiagnosticsRevision3FaultSequenceEntry_t,      ENDIANNESS_SWAP,   IO_None,    NvErd,   RecordErds_GetDefaultZero      ) \
   \
   ENTRY(Erd_FrontendUiConfiguration,                                    0xF000,    LcdUiConfiguration_t,                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_StoreFrontendUiConfigurationRequest,                        0xF001,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CookRequest_Cavity1,                                        0xF002,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DoorLockStatus_Cavity1,                                     0xF003,    DoorLockStatus_t,                                     ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DoorPosition_Cavity1,                                       0xF009,    DoorPosition_t,                                       ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_IsRunningPreheat_Cavity1,                                   0xF00E,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_IsRunningSelfCleanS2_Cavity1,                               0xF010,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_IsRunningSelfCleanCoolDown_Cavity1,                         0xF011,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_IsRunningSteamCleanCoolDown_Cavity1,                        0xF02C,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CurrentVirtualTemperature_Cavity1,                          0xF030,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_PreheatCompleted_Cavity1,                                   0xF031,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DelayTime_Cavity1,                                          0xF035,    DelayTime_t,                                          ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CookTimeCountdownTime_Cavity1,                              0xF036,    CountDownTime_t,                                      ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CookStatus_Cavity1,                                         0xF038,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CookStatusFrontend_Cavity1,                                 0xF039,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DoorLockServiceModeRequest_Cavity1,                         0xF048,    DoorLockRequest_t,                                    ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UserOffset_Cavity1,                                         0xF067,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_CavityConfiguration,                                        0xF0AC,    CavityConfiguration_t,                                ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SelfCleanPendingRequest_Cavity1,                            0xF0AD,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SelfCleanPendingStatus_Cavity1,                             0xF0AF,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SelfCleanPendingStatusFrontend_Cavity1,                     0xF0B0,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_MiswireStatus_Cavity1,                                      0xF0B1,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_OtaUpdateStatusToFrontend,                                  0xF0C0,    OtaUpdateStatus_t,                                    ENDIANNESS_FREE,   IO_All,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_CookRequest_Cavity2,                                        0xF102,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DoorLockStatus_Cavity2,                                     0xF103,    DoorLockStatus_t,                                     ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DoorPosition_Cavity2,                                       0xF109,    DoorPosition_t,                                       ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_IsRunningPreheat_Cavity2,                                   0xF10E,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_IsRunningSelfCleanS2_Cavity2,                               0xF110,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_IsRunningSelfCleanCoolDown_Cavity2,                         0xF111,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DoorLockServiceModeStatus_Cavity1,                          0xF117,    DoorLockStatus_t,                                     ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_IsRunningSteamCleanCoolDown_Cavity2,                        0xF12C,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CurrentVirtualTemperature_Cavity2,                          0xF130,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_PreheatCompleted_Cavity2,                                   0xF131,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DelayTime_Cavity2,                                          0xF135,    DelayTime_t,                                          ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CookTimeCountdownTime_Cavity2,                              0xF136,    CountDownTime_t,                                      ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CookStatus_Cavity2,                                         0xF138,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CookStatusFrontend_Cavity2,                                 0xF139,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DoorLockServiceModeRequest_Cavity2,                         0xF148,    DoorLockRequest_t,                                    ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UserOffset_Cavity2,                                         0xF167,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_All,     NvErd,   RecordErds_GetDefaultZero      ) \
   ENTRY(Erd_SelfCleanPendingRequest_Cavity2,                            0xF168,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SelfCleanPendingStatus_Cavity2,                             0xF169,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SelfCleanPendingStatusFrontend_Cavity2,                     0xF16A,    CookEngineStatus_t,                                   ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_MiswireStatus_Cavity2,                                      0xF1B1,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_FaultIsActive,                                              0xF200,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RiskAddressStateFaultActive,                                0xF201,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DisplayFaultIsActive,                                       0xF202,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_StopCookFaultIsActive,                                      0xF203,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CancelSelfCleanFaultIsActive,                               0xF204,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_MiswireIsActive,                                            0xF205,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_StopCookToMc,                                               0xF206,    bool,                                                 ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_HighestPriorityDisplayFault,                                0xF210,    uint16_t,                                             ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ClearFaults,                                                0xF211,    Signal_t,                                             ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_FaultCleared,                                               0xF212,    Signal_t,                                             ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_FaultOccured,                                               0xF213,    Signal_t,                                             ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ClearRemoteFaultsSignal,                                    0xF214,    Signal_t,                                             ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DoorLockServiceModeStatus_Cavity2,                          0xF217,    DoorLockStatus_t,                                     ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_IsDoubleOven,                                               0xF220,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ResolvedDoorLockStatus,                                     0xF221,    DoorLockStatus_t,                                     ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_TimeOfDayFromMc,                                            0xF222,    TimeOfDay_t,                                          ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_LcdUiInBootloaderMode,                                      0xF223,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_HeartbeatEnableAfterUiStartup,                              0xF226,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_FrontendHeartbeatFault,                                     0xF227,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ConnectedAppHeartbeatFault,                                 0xF228,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RecipeDownloadRequestToConnectedApp,                        0xF230,    RecipeExecutionId_t,                                  ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RecipeDownloadStatusFromConnectedApp,                       0xF231,    RecipeDownloadStatus_t,                               ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RecipeRequestToFrontEnd,                                    0xF232,    RecipeStatus_t,                                       ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RecipeStatusFromFrontEnd,                                   0xF233,    RecipeStatus_t,                                       ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RemoteRecipeRequest,                                        0xF234,    RecipeStatus_t,                                       ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RecipeDownloadStatusToFrontEnd,                             0xF235,    RecipeDownloadStatus_t,                               ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RecipeMediaDownloadRequestToConnectedApp,                   0xF236,    uint8_t,                                              ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_SettingsInitializationInProgress,                           0xF300,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SettingsInitializationCompleted,                            0xF301,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_BundledSettings,                                            0xF302,    BundledSettings_t,                                    ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SoundSettingsFromMc,                                        0xF303,    SoundSettings_t,                                      ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SoundSettingsToMc,                                          0xF304,    SoundSettings_t,                                      ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_BundledSettingsRequested,                                   0xF305,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CookingSettingsFromUi,                                      0xF306,    CookingSettings_t,                                    ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_TemperatureUnitFromMc,                                      0xF307,    TemperatureUnit_t,                                    ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_AutoRecipeEnabledFromMc,                                    0xF308,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_TwelveHourShutoffEnabledFromMc,                             0xF309,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UserOffsetUpperFromMc,                                      0xF30A,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UserOffsetLowerFromMc,                                      0xF30B,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_TemperatureUnitToMc,                                        0xF30C,    TemperatureUnit_t,                                    ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_AutoRecipeEnabledToMc,                                      0xF30D,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_TwelveHourShutoffEnabledToMc,                               0xF30E,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UserOffsetUpperToMc,                                        0xF30F,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UserOffsetLowerToMc,                                        0xF310,    Temperature_t,                                        ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DisplaySettingsFromMc,                                      0xF311,    DisplaySettings_t,                                    ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DisplaySettingsToMc,                                        0xF312,    DisplaySettings_t,                                    ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WiFiData,                                                   0xF313,    WiFiData_t,                                           ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WiFiNetworkStatusUpdate,                                    0xF315,    WiFiNetworkStatusUpdate_t,                            ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_TimeOfDayToMc,                                              0xF316,    TimeOfDay_t,                                          ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SecondsSinceMidnightToMc,                                   0xF317,    uint32_t,                                             ENDIANNESS_SWAP,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_Wlan0MacAddress,                                            0xF318,    WiFiMacAddress_t,                                     ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ClearUserData,                                              0xF319,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RemoteEnabledToMc,                                          0xF31A,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SabbathModeActiveFromMc,                                    0xF31B,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SabbathModeActiveToMc,                                      0xF31C,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_RemoteEnabledFromMc,                                        0xF31D,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_VersionRequestSignal,                                       0xF31E,    Signal_t,                                             ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_PrimaryMcVersion,                                           0xF31F,    ApplicationVersionCharacters_t,                       ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SecondaryMcVersion,                                         0xF320,    ApplicationVersionCharacters_t,                       ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_StuiVersion,                                                0xF321,    ApplicationVersionCharacters_t,                       ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_ControlLockStatusFromMc,                                    0xF323,    ControlLockoutStatus_t,                               ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ControlLockStatusToMc,                                      0xF324,    ControlLockoutStatus_t,                               ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_PrimaryOvenDiagnosticsFaultTableClearDebounced,             0xF325,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SecondaryOvenDiagnosticsFaultTableClearDebounced,           0xF326,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ClockTypeFromMc,                                            0xF327,    bool,                                                 ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UiHeartbeatApiVersionFromCavity1,                           0xF328,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UiHeartbeatApiVersionFromCavity2,                           0xF329,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UiHeartbeatApiVersionRequiredMC,                            0xF330,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UiHeartbeatApiVersionFromStui,                              0xF332,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_SoftwareApiMismatchDetected,                                0xF333,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UiHeartbeatApiVersionRequiredStui,                          0xF334,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_WiFiServiceState,                                           0xF350,    WiFiServiceState_t,                                   ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WiFiServiceRequest,                                         0xF351,    WiFiServiceRequest_t,                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WiFiSoftwareUpdateStarted,                                  0xF352,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WiFiSoftwareUpdateStatus,                                   0xF353,    uint8_t,                                              ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WiFiUpdateChoice,                                           0xF354,    uint8_t,                                              ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_ConsumerWiFiNetworkSsid,                                    0xF355,    WiFiNetworkName_t,                                    ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ConsumerWiFiNetworkPassphrase,                              0xF356,    WiFiPassword_t,                                       ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_LowPowerModeActive,                                         0xF357,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UpdatedRecipeInfoDataRequest,                               0xF358,    uint8_t,                                              ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_UpdatedRecipeInfoDataResponse,                              0xF359,    uint8_t,                                              ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_BoardModelNumber,                                           0xF360,    ModelNumber_t,                                        ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_BoardSerialNumber,                                          0xF361,    SerialNumber_t,                                       ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_EnterServiceMode,                                           0xF383,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ServiceModeActive,                                          0xF384,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_IsClockSet,                                                 0xF400,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ErrorParsingRecipeData,                                     0xF401,    bool,                                                 ENDIANNESS_FREE,   IO_O,       RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ConvectionFanServiceModeRequest_Cavity1,                    0xF622,    ConvectionFanState_t,                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ConvectionFanServiceModeRequest_Cavity2,                    0xF623,    ConvectionFanState_t,                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_OvenLightServiceModeRequest_Cavity1,                        0xF624,    OvenLightRequest_t,                                   ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_OvenLightServiceModeRequest_Cavity2,                        0xF625,    OvenLightRequest_t,                                   ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ElementRequestOverride_Cavity1,                             0xF827,    HeatingElementBitmap_t,                               ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CoolingFanServiceModeRequest_Cavity1,                       0xF828,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_ElementRequestOverride_Cavity2,                             0xF927,    HeatingElementBitmap_t,                               ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CoolingFanServiceModeRequest_Cavity2,                       0xF928,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_StopCooktopFaultIsActive,                                   0xFC10,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(E_ERD_CLEAR_REMOTE_FAULTS_SIGNAL,                               0xFC11,    Signal_t,                                             ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_InternalServiceDiagnosticsManifest,                         0xFC13,    ServiceDiagnosticsRevision3Manifest_t,                ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_AvailableRemoteCookModesFromPrimaryMc,                      0xFD10,    RemoteAvailableCookModes_t,                           ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_AvailableRemoteCookModesFromSecondaryMc,                    0xFD11,    RemoteAvailableCookModes_t,                           ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_CompatibilityEolStuiTouchRequest,                           0xFE0B,    bool,                                                 ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_CompatibilityEolStuiTouchSignal,                            0xFE0C,    Signal_t,                                             ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_HeartbeatEnable,                                            0xFF00,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_ConnectedHeartbeatEnable,                                   0xFF01,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_StuiEolHeartbeatEnable,                                     0xFF02,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_HeartbeatTickFromPrimaryMc,                                 0xFF38,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_HeartbeatTickFromFrontendApp,                               0xFF39,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_HeartbeatTickFromSecondaryMc,                               0xFF3A,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_TimerModule,                                                0xFF3B,    TimerModule_t *,                                      ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_HeartbeatTickFromConnectedApp,                              0xFF3C,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_KitchenTimerFromFrontend,                                   0xFF3D,    TimeInMinutes_t,                                      ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_KitchenTimerToFrontend,                                     0xFF3E,    TimeInMinutes_t,                                      ENDIANNESS_SWAP,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DemoModeIsActive,                                           0xFF40,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_DemoModeRequestFromFrontend,                                0xFF41,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(Erd_Null,                                                       0xFFFB,    uint8_t,                                              ENDIANNESS_FREE,   IO_All,     RamErd,  RamErd                         ) \
   ENTRY(Erd_WelcomeEolStuiTouchSignal,                                  0xFFFC,    Signal_t,                                             ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WelcomeEolLcdTouch,                                         0xFFFD,    Signal_t,                                             ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \
   ENTRY(Erd_WelcomeEolRequest,                                          0xFFFE,    bool,                                                 ENDIANNESS_FREE,   IO_All,     RamErd,  NoDefaultValue                 ) \
   \
   ENTRY(E_ERD_RESERVED,                                                 0xFFFF,    uint8_t,                                              ENDIANNESS_FREE,   IO_None,    RamErd,  NoDefaultValue                 ) \

#define ERD_EXPAND_AS_ENUM(ErdEnum, ID, DataType, EndiannessAware, InOutConfig, StorageLoc, NonVolatileDefaultData) ErdEnum = ID,

enum
{
   ERD_TABLE(ERD_EXPAND_AS_ENUM)
   ENUM_DUMMY_USED_FOR_XMACRO_COMPILE_WARNING};

/*!
 * Definition of ERDs that exist on a different board.
 */
#define OFFBOARD_ERD_TABLE(ENTRY) \
   ENTRY(Erd_ClockTypeOnMc,                                    0x0006) \
   ENTRY(Erd_TemperatureUnitOnMc,                              0x0007) \
   ENTRY(Erd_TwelveHourShutoffEnabledOnMc,                     0x5000) \
   ENTRY(Erd_AutoRecipeEnabledOnMc,                            0x5003) \
   ENTRY(Erd_CookRequestMc,                                    0xF002) \
   ENTRY(Erd_DoorLockServiceModeRequestMc,                     0xF048) \
   ENTRY(Erd_OvenLightRequestMc,                               0xF007) \
   ENTRY(Erd_OvenLightServiceModeRequestMc,                    0xF624) \
   ENTRY(Erd_SelfCleanPendingRequestMc,                        0xF01C) \
   ENTRY(Erd_ServiceModeActiveMc,                              0xF384) \
   ENTRY(Erd_HeartbeatTickMc,                                  0xF3F7) \
   ENTRY(Erd_DemoModeOnMc,                                     0xF3FD) \
   ENTRY(Erd_ConvectionFanServiceModeRequestMc,                0xF622) \
   ENTRY(Erd_ElementServiceModeRequestMc,                      0xF827) \
   ENTRY(Erd_CoolingFanServiceModeRequestMc,                   0xF627) \
   ENTRY(Erd_OvenDiagnosticsFaultTableClearOnMc,               0xE104) \
   ENTRY(Erd_SoundSettingsOnMc,                                0xFF50) \
   ENTRY(Erd_DisplaySettingsOnMc,                              0xFF51) \
   ENTRY(Erd_UserOffsetUpperOnMc,                              0xF067) \
   ENTRY(Erd_UserOffsetLowerOnMc,                              0xF167) \
   ENTRY(Erd_UiStartupToMc,                                    0xF226) \
   ENTRY(Erd_SecondsSinceMidnightOnMc,                         0xF310) \
   ENTRY(Erd_RemoteEnabledOnMc,                                0xF3BE) \
   ENTRY(Erd_StopCookFaultIsActiveOnMc,                        0xF3CB) \
   ENTRY(Erd_ResetOnFaultDismissalOnMc,                        0xF3CD) \
   ENTRY(Erd_SabbathModeActiveOnMc,                            0x0009) \
   ENTRY(Erd_ControlLockStatusOnMc,                            0xFF52) \
   ENTRY(Erd_FrontendHeartbeatFaultOnMc,                       0xF3FF) \
   ENTRY(Erd_ConnectedAppHeartbeatFaultOnMc,                   0xF400) \
   ENTRY(Erd_ClockHasBeenSetOnMc,                              0xF401) \
   ENTRY(Erd_WelcomeEolEnableOnStui,                           0xFE0A) \
   ENTRY(Erd_WelcomeEolTouchRequestOnStui,                     0xFE0B) \

#define REMOTE_ERD_TABLE(ENTRY)    \
   ENTRY(Erd_ClockTimeRemote,                                      0x0005,    TimeHms_t) \
   ENTRY(Erd_ClockTypeRemote,                                      0x0006,    ClockType_t) \
   ENTRY(Erd_TemperatureUnitRemote,                                0x0007,    TemperatureUnit_t) \
   ENTRY(Erd_SabbathModeRemote,                                    0x0009,    bool) \
   ENTRY(Erd_SoundLevelRemote,                                     0x000A,    SoundLevel_t) \
   ENTRY(Erd_ServiceModeStateRequest,                              0x0036,    bool) \
   ENTRY(Erd_ServiceModeState,                                     0x0037,    bool) \
   ENTRY(Erd_KitchenTimer_Remote,                                  0x0050,    TimeInMinutes_t) \
   ENTRY(Erd_12HourShutOffRemote,                                  0x5000,    bool) \
   ENTRY(Erd_EndToneTypeRemote,                                    0x5001,    EndToneType_t) \
   ENTRY(Erd_AutoRecipeEnableRemote,                               0x5003,    bool) \
   ENTRY(E_ERD_ELAPSED_ON_TIME_PLACEHOLDER_REMOTE,                 0x5004,    uint8_t) \
   ENTRY(E_ERD_OVEN_CONFIG_REMOTE,                                 0x5007,    RemoteOvenConfiguration_t) \
   ENTRY(E_ERD_OVEN_MODE_MIN_MAX_TEMPS_REMOTE,                     0x5008,    OvenModeMinMaxTemp_t) \
   \
   ENTRY(E_ERD_COOK_MODE_COMMAND_Cavity1_REMOTE,                   0x5100,    RemoteCookRequest_t) \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity1_REMOTE,                  0x5101,    uint8_t) \
   ENTRY(Erd_UserOffset_Cavity1_REMOTE,                            0x5106,    int8_t) \
   ENTRY(Erd_RemoteEnabled_Cavity1,                                0x510A,    bool) \
   ENTRY(E_ERD_AVAILABLE_COOK_MODES_Cavity1_REMOTE,                0x510B,    RemoteAvailableCookModes_t) \
   \
   ENTRY(E_ERD_COOK_MODE_COMMAND_Cavity2_REMOTE,                   0x5200,    RemoteCookRequest_t) \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity2_REMOTE,                  0x5201,    uint8_t) \
   ENTRY(Erd_UserOffset_Cavity2_REMOTE,                            0x5206,    int8_t) \
   ENTRY(Erd_RemoteEnabled_Cavity2,                                0x520A,    bool) \
   ENTRY(E_ERD_AVAILABLE_COOK_MODES_Cavity2_REMOTE,                0x520B,    RemoteAvailableCookModes_t) \
   ENTRY(Erd_RecipeStatusRemote,                                   0x5300,    RecipeStatus_t) \

#define CALLBACK_TABLE(ENTRY) \
   ENTRY(E_ERD_COOK_MODE_COMMAND_Cavity1_REMOTE,           RemoteCookRequest_t,         RemoteErdConvertedCallBack_WriteCookRequest_Cavity1,       RemoteErdConvertedCallBack_ReadCookRequest_Cavity1) \
   ENTRY(E_ERD_COOK_MODE_COMMAND_Cavity2_REMOTE,           RemoteCookRequest_t,         RemoteErdConvertedCallBack_WriteCookRequest_Cavity2,       RemoteErdConvertedCallBack_ReadCookRequest_Cavity2) \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity1_REMOTE,          uint8_t,                     RemoteErdConvertedCallBack_WriteNotAvailable,              RemoteErdConvertedCallBack_ReadOvenStatus_Cavity1)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity2_REMOTE,          uint8_t,                     RemoteErdConvertedCallBack_WriteNotAvailable,              RemoteErdConvertedCallBack_ReadOvenStatus_Cavity2)  \
   ENTRY(E_ERD_AVAILABLE_COOK_MODES_Cavity1_REMOTE,        RemoteAvailableCookModes_t,  RemoteErdConvertedCallBack_WriteNotAvailable,              RemoteErdConvertedCallBack_ReadAvailableCookModes_Cavity1)   \
   ENTRY(E_ERD_AVAILABLE_COOK_MODES_Cavity2_REMOTE,        RemoteAvailableCookModes_t,  RemoteErdConvertedCallBack_WriteNotAvailable,              RemoteErdConvertedCallBack_ReadAvailableCookModes_Cavity2)   \
   ENTRY(E_ERD_OVEN_MODE_MIN_MAX_TEMPS_REMOTE,             OvenModeMinMaxTemp_t,        RemoteErdConvertedCallBack_WriteNotAvailable,              RemoteErdConvertedCallBack_ReadOvenMinMaxTemps)  \
   ENTRY(E_ERD_OVEN_CONFIG_REMOTE,                         RemoteOvenConfiguration_t,   RemoteErdConvertedCallBack_WriteNotAvailable,              RemoteErdConvertedCallBack_ReadOvenConfiguration)  \
   ENTRY(E_ERD_ELAPSED_ON_TIME_PLACEHOLDER_REMOTE,         uint8_t,                     RemoteErdConvertedCallBack_WriteNotAvailable,              RemoteErdConvertedCallBack_ReadZeroOneByteData)  \
   ENTRY(Erd_ClockTimeRemote,                              TimeHms_t,                   RemoteErdConvertedCallBack_WriteClockTime,                 RemoteErdConvertedCallBack_ReadClockTime)  \
   ENTRY(Erd_ClockTypeRemote,                              ClockType_t,                 RemoteErdConvertedCallBack_WriteClockType,                 RemoteErdConvertedCallBack_ReadClockType)  \
   ENTRY(Erd_SabbathModeRemote,                            bool,                        RemoteErdConvertedCallBack_WriteSabbathModeActive,         RemoteErdConvertedCallBack_ReadSabbathModeActive)  \
   ENTRY(Erd_12HourShutOffRemote,                          bool,                        RemoteErdConvertedCallBack_Write12HourShutOff,             RemoteErdConvertedCallBack_Read12HourShutOff)  \
   ENTRY(Erd_AutoRecipeEnableRemote,                       bool,                        RemoteErdConvertedCallBack_WriteAutoRecipeEnable,          RemoteErdConvertedCallBack_ReadAutoRecipeEnable)  \
   ENTRY(Erd_SoundLevelRemote,                             SoundLevel_t,                RemoteErdConvertedCallBack_WriteSoundLevel,                RemoteErdConvertedCallBack_ReadSoundLevel)  \
   ENTRY(Erd_EndToneTypeRemote,                            EndToneType_t,               RemoteErdConvertedCallBack_WriteEndToneType,               RemoteErdConvertedCallBack_ReadEndToneType)  \
   ENTRY(Erd_UserOffset_Cavity1_REMOTE,                    int8_t,                      RemoteErdConvertedCallBack_WriteUserOffSetTemp_Cavity1,    RemoteErdConvertedCallBack_ReadUserOffSetTemp_Cavity1)  \
   ENTRY(Erd_UserOffset_Cavity2_REMOTE,                    int8_t,                      RemoteErdConvertedCallBack_WriteUserOffSetTemp_Cavity2,    RemoteErdConvertedCallBack_ReadUserOffSetTemp_Cavity2)  \
   ENTRY(Erd_RemoteEnabled_Cavity1,                        bool,                        RemoteErdConvertedCallBack_WriteNotAvailable,              RemoteErdConvertedCallBack_ReadRemoteEnabled) \
   ENTRY(Erd_RemoteEnabled_Cavity2,                        bool,                        RemoteErdConvertedCallBack_WriteNotAvailable,              RemoteErdConvertedCallBack_ReadRemoteEnabled) \
   ENTRY(Erd_TemperatureUnitRemote,                        TemperatureUnit_t,           RemoteErdConvertedCallBack_WriteTemperatureUnit,           RemoteErdConvertedCallBack_ReadTemperatureUnit) \
   ENTRY(Erd_KitchenTimer_Remote,                          TimeInMinutes_t,             RemoteErdConvertedCallBack_WriteKitchenTimer,              RemoteErdConvertedCallBack_ReadKitchenTimer) \
   ENTRY(Erd_RecipeStatusRemote,                           RecipeStatus_t,              RemoteErdConvertedCallBack_WriteRecipeStatus,              RemoteErdConvertedCallBack_ReadRecipeStatus) \

#define DEPENDENCY_TABLE(ENTRY) \
   ENTRY(E_ERD_COOK_MODE_COMMAND_Cavity1_REMOTE,        Erd_CookStatus_Cavity1) \
   ENTRY(E_ERD_COOK_MODE_COMMAND_Cavity1_REMOTE,        Erd_DelayTime_Cavity1) \
   ENTRY(E_ERD_COOK_MODE_COMMAND_Cavity1_REMOTE,        Erd_CookTimeRemainingMinutes_Cavity1) \
   ENTRY(E_ERD_COOK_MODE_COMMAND_Cavity2_REMOTE,        Erd_CookStatus_Cavity2) \
   ENTRY(E_ERD_COOK_MODE_COMMAND_Cavity2_REMOTE,        Erd_DelayTime_Cavity2) \
   ENTRY(E_ERD_COOK_MODE_COMMAND_Cavity2_REMOTE,        Erd_CookTimeRemainingMinutes_Cavity2) \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity1_REMOTE,       Erd_CookStatus_Cavity1)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity1_REMOTE,       Erd_IsRunningSelfCleanS2_Cavity1)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity1_REMOTE,       Erd_IsRunningSelfCleanCoolDown_Cavity1)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity1_REMOTE,       Erd_IsRunningSteamCleanCoolDown_Cavity1)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity1_REMOTE,       Erd_DelayTime_Cavity1)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity1_REMOTE,       Erd_IsRunningPreheat_Cavity1)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity2_REMOTE,       Erd_CookStatus_Cavity2)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity2_REMOTE,       Erd_IsRunningSelfCleanS2_Cavity2)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity2_REMOTE,       Erd_IsRunningSelfCleanCoolDown_Cavity2)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity2_REMOTE,       Erd_IsRunningSteamCleanCoolDown_Cavity2)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity2_REMOTE,       Erd_DelayTime_Cavity2)  \
   ENTRY(E_ERD_OVEN_CURRENT_STATE_Cavity2_REMOTE,       Erd_IsRunningPreheat_Cavity2)  \
   ENTRY(Erd_UserOffset_Cavity1_REMOTE,                 Erd_UserOffset_Cavity1) \
   ENTRY(Erd_UserOffset_Cavity2_REMOTE,                 Erd_UserOffset_Cavity2) \
   ENTRY(Erd_RemoteEnabled_Cavity1,                     Erd_RemoteEnabledToMc) \
   ENTRY(Erd_RemoteEnabled_Cavity2,                     Erd_RemoteEnabledToMc) \
   ENTRY(Erd_TemperatureUnitRemote,                     Erd_TemperatureUnitFromMc) \
   ENTRY(Erd_12HourShutOffRemote,                       Erd_TwelveHourShutoffEnabledFromMc) \
   ENTRY(Erd_ClockTypeRemote,                           Erd_ClockTypeFromMc) \
   ENTRY(Erd_EndToneTypeRemote,                         Erd_SoundSettingsFromMc) \
   ENTRY(Erd_SoundLevelRemote,                          Erd_SoundSettingsFromMc) \
   ENTRY(Erd_AutoRecipeEnableRemote,                    Erd_AutoRecipeEnabledFromMc) \
   ENTRY(Erd_SabbathModeRemote,                         Erd_SabbathModeActiveFromMc) \
   ENTRY(Erd_KitchenTimer_Remote,                       Erd_KitchenTimerFromFrontend) \
   ENTRY(Erd_RecipeStatusRemote,                        Erd_RecipeStatusFromFrontEnd) \

#define EXPAND_OFFBOARD_ERD_TABLE_AS_ENUM(ErdEnum, ID) ErdEnum = ID,

#define EXPAND_REMOTE_ERD_TABLE_AS_ENUM(ErdEnum, ID, type) ErdEnum = ID,

#define EXPAND_REMOTE_ERD_TABLE_AS_DUPLICATE_PREVENTION_ENUM(ErdEnum, ID, type) RC15DUPLICATE ## ID,

#define EXPAND_AS_INDIRECT_ELEMENTS(VirtualErd, DataType, WriteCallback, ReadCallback) \
   { VirtualErd, sizeof(DataType), WriteCallback, ReadCallback },

#define EXPAND_AS_DEPENDENCY_ELEMENTS(VirtualErd, RealErdForVirtualErd ) \
   { VirtualErd, RealErdForVirtualErd },

enum
{
   OFFBOARD_ERD_TABLE(EXPAND_OFFBOARD_ERD_TABLE_AS_ENUM)
   ENUM_OFFBOARD_DUMMY_USED_FOR_XMACRO_COMPILE_WARNING};

enum
{
   REMOTE_ERD_TABLE(EXPAND_REMOTE_ERD_TABLE_AS_ENUM)
   ENUM_REMOTE_DUMMY_USED_FOR_XMACRO_COMPILE_WARNING};

// the following #define and XMACRO expansion prevent ERD ID duplication in E2Studio.
// The enumeration created should not be used for anything because there is no meaning.
// If a ERD ID is used more than once in the ERD_TABLE this
// enumeration will cause the following error in the compile.
//     C5101 (E) "RANGEDUPLICATE0x????" has already been declared in the current scope
#define EXPAND_AS_DUPLICATE_PREVENTION_ENUM(ErdEnum, ID, DataType, EndiannessAware, InOutConfig, StorageLoc, NonVolatileDefaultData) RANGEDUPLICATE ## ID,

enum
{
   ERD_TABLE(EXPAND_AS_DUPLICATE_PREVENTION_ENUM)
   REMOTE_ERD_TABLE(EXPAND_REMOTE_ERD_TABLE_AS_DUPLICATE_PREVENTION_ENUM)
   RANGE_DUPLICATE_PREVENTION_MAX
};

#endif
