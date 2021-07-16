
"use strict";

let WaypointPull = require('./WaypointPull.js')
let MessageInterval = require('./MessageInterval.js')
let FileTruncate = require('./FileTruncate.js')
let CommandInt = require('./CommandInt.js')
let CommandLong = require('./CommandLong.js')
let LogRequestList = require('./LogRequestList.js')
let SetMode = require('./SetMode.js')
let FileList = require('./FileList.js')
let CommandTOL = require('./CommandTOL.js')
let FileRename = require('./FileRename.js')
let WaypointClear = require('./WaypointClear.js')
let ParamPush = require('./ParamPush.js')
let LogRequestData = require('./LogRequestData.js')
let FileRemove = require('./FileRemove.js')
let FileWrite = require('./FileWrite.js')
let SetMavFrame = require('./SetMavFrame.js')
let FileChecksum = require('./FileChecksum.js')
let ParamPull = require('./ParamPull.js')
let FileClose = require('./FileClose.js')
let WaypointSetCurrent = require('./WaypointSetCurrent.js')
let VehicleInfoGet = require('./VehicleInfoGet.js')
let CommandBool = require('./CommandBool.js')
let MountConfigure = require('./MountConfigure.js')
let ParamSet = require('./ParamSet.js')
let ParamGet = require('./ParamGet.js')
let FileMakeDir = require('./FileMakeDir.js')
let FileRead = require('./FileRead.js')
let CommandTriggerControl = require('./CommandTriggerControl.js')
let CommandTriggerInterval = require('./CommandTriggerInterval.js')
let CommandVtolTransition = require('./CommandVtolTransition.js')
let FileRemoveDir = require('./FileRemoveDir.js')
let CommandHome = require('./CommandHome.js')
let WaypointPush = require('./WaypointPush.js')
let StreamRate = require('./StreamRate.js')
let FileOpen = require('./FileOpen.js')
let LogRequestEnd = require('./LogRequestEnd.js')

module.exports = {
  WaypointPull: WaypointPull,
  MessageInterval: MessageInterval,
  FileTruncate: FileTruncate,
  CommandInt: CommandInt,
  CommandLong: CommandLong,
  LogRequestList: LogRequestList,
  SetMode: SetMode,
  FileList: FileList,
  CommandTOL: CommandTOL,
  FileRename: FileRename,
  WaypointClear: WaypointClear,
  ParamPush: ParamPush,
  LogRequestData: LogRequestData,
  FileRemove: FileRemove,
  FileWrite: FileWrite,
  SetMavFrame: SetMavFrame,
  FileChecksum: FileChecksum,
  ParamPull: ParamPull,
  FileClose: FileClose,
  WaypointSetCurrent: WaypointSetCurrent,
  VehicleInfoGet: VehicleInfoGet,
  CommandBool: CommandBool,
  MountConfigure: MountConfigure,
  ParamSet: ParamSet,
  ParamGet: ParamGet,
  FileMakeDir: FileMakeDir,
  FileRead: FileRead,
  CommandTriggerControl: CommandTriggerControl,
  CommandTriggerInterval: CommandTriggerInterval,
  CommandVtolTransition: CommandVtolTransition,
  FileRemoveDir: FileRemoveDir,
  CommandHome: CommandHome,
  WaypointPush: WaypointPush,
  StreamRate: StreamRate,
  FileOpen: FileOpen,
  LogRequestEnd: LogRequestEnd,
};
