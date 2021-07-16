
"use strict";

let ADSBVehicle = require('./ADSBVehicle.js');
let AttitudeTarget = require('./AttitudeTarget.js');
let HilActuatorControls = require('./HilActuatorControls.js');
let Vibration = require('./Vibration.js');
let ManualControl = require('./ManualControl.js');
let EstimatorStatus = require('./EstimatorStatus.js');
let ActuatorControl = require('./ActuatorControl.js');
let GlobalPositionTarget = require('./GlobalPositionTarget.js');
let HomePosition = require('./HomePosition.js');
let WaypointReached = require('./WaypointReached.js');
let WaypointList = require('./WaypointList.js');
let Waypoint = require('./Waypoint.js');
let State = require('./State.js');
let WheelOdomStamped = require('./WheelOdomStamped.js');
let VFR_HUD = require('./VFR_HUD.js');
let Altitude = require('./Altitude.js');
let HilSensor = require('./HilSensor.js');
let HilStateQuaternion = require('./HilStateQuaternion.js');
let LandingTarget = require('./LandingTarget.js');
let RCOut = require('./RCOut.js');
let HilGPS = require('./HilGPS.js');
let LogEntry = require('./LogEntry.js');
let DebugValue = require('./DebugValue.js');
let OnboardComputerStatus = require('./OnboardComputerStatus.js');
let CompanionProcessStatus = require('./CompanionProcessStatus.js');
let VehicleInfo = require('./VehicleInfo.js');
let Mavlink = require('./Mavlink.js');
let FileEntry = require('./FileEntry.js');
let ExtendedState = require('./ExtendedState.js');
let PositionTarget = require('./PositionTarget.js');
let Trajectory = require('./Trajectory.js');
let LogData = require('./LogData.js');
let TimesyncStatus = require('./TimesyncStatus.js');
let RadioStatus = require('./RadioStatus.js');
let CamIMUStamp = require('./CamIMUStamp.js');
let ParamValue = require('./ParamValue.js');
let CommandCode = require('./CommandCode.js');
let OpticalFlowRad = require('./OpticalFlowRad.js');
let MountControl = require('./MountControl.js');
let RTCM = require('./RTCM.js');
let StatusText = require('./StatusText.js');
let Thrust = require('./Thrust.js');
let BatteryStatus = require('./BatteryStatus.js');
let Param = require('./Param.js');
let HilControls = require('./HilControls.js');
let RCIn = require('./RCIn.js');
let OverrideRCIn = require('./OverrideRCIn.js');

module.exports = {
  ADSBVehicle: ADSBVehicle,
  AttitudeTarget: AttitudeTarget,
  HilActuatorControls: HilActuatorControls,
  Vibration: Vibration,
  ManualControl: ManualControl,
  EstimatorStatus: EstimatorStatus,
  ActuatorControl: ActuatorControl,
  GlobalPositionTarget: GlobalPositionTarget,
  HomePosition: HomePosition,
  WaypointReached: WaypointReached,
  WaypointList: WaypointList,
  Waypoint: Waypoint,
  State: State,
  WheelOdomStamped: WheelOdomStamped,
  VFR_HUD: VFR_HUD,
  Altitude: Altitude,
  HilSensor: HilSensor,
  HilStateQuaternion: HilStateQuaternion,
  LandingTarget: LandingTarget,
  RCOut: RCOut,
  HilGPS: HilGPS,
  LogEntry: LogEntry,
  DebugValue: DebugValue,
  OnboardComputerStatus: OnboardComputerStatus,
  CompanionProcessStatus: CompanionProcessStatus,
  VehicleInfo: VehicleInfo,
  Mavlink: Mavlink,
  FileEntry: FileEntry,
  ExtendedState: ExtendedState,
  PositionTarget: PositionTarget,
  Trajectory: Trajectory,
  LogData: LogData,
  TimesyncStatus: TimesyncStatus,
  RadioStatus: RadioStatus,
  CamIMUStamp: CamIMUStamp,
  ParamValue: ParamValue,
  CommandCode: CommandCode,
  OpticalFlowRad: OpticalFlowRad,
  MountControl: MountControl,
  RTCM: RTCM,
  StatusText: StatusText,
  Thrust: Thrust,
  BatteryStatus: BatteryStatus,
  Param: Param,
  HilControls: HilControls,
  RCIn: RCIn,
  OverrideRCIn: OverrideRCIn,
};
