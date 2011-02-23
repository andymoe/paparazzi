/*
 * Copyright (C) 2011 The Paparazzi Team
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * @file state.h
 *   @brief General inteface for the main vehicle states.
 *
 *   This is the more detailed description of this file.
 *
 *   @author Felix Ruess <felix.ruess@gmail.com>
 *
 */

#ifndef STATE_H
#define STATE_H

#include "math/pprz_algebra_int.h"
#include "math/pprz_algebra_float.h"
#include "math/pprz_geodetic_int.h"
#include "math/pprz_geodetic_float.h"

#include "std.h"
#include <string.h>

/**
 * @defgroup PosGroup position representations
 * @{
 */
#define POS_ECEF_I 1<<0
#define POS_NED_I  1<<1
#define POS_LLA_I  1<<2
#define POS_UTM_I  1<<3
#define POS_ECEF_F 1<<4
#define POS_NED_F  1<<5
#define POS_LLA_F  1<<6
#define POS_UTM_F  1<<7
/**@}*/

/**
 * @defgroup SpeedGroup ground-speed representations
 * @{
 */
#define SPEED_ECEF_I  1<<0
#define SPEED_NED_I   1<<1
#define SPEED_HNORM_I 1<<2
#define SPEED_HDIR_I  1<<3
#define SPEED_ECEF_F  1<<4
#define SPEED_NED_F   1<<5
#define SPEED_HNORM_F 1<<6
#define SPEED_HDIR_F  1<<7
/**@}*/

/**
 * @defgroup AccelGroup acceleration representations
 * @{
 */
#define ACCEL_ECEF_I 1<<0
#define ACCEL_NED_I  1<<1
#define ACCEL_ECEF_F 1<<3
#define ACCEL_NED_F  1<<4
/**@}*/

/**
 * @defgroup AttGroup attitude representations
 * @{
 */
#define ATT_QUAT_I  1<<0
#define ATT_EULER_I 1<<1
#define ATT_RMAT_I  1<<2
#define ATT_QUAT_F  1<<3
#define ATT_EULER_F 1<<4
#define ATT_RMAT_F  1<<5
/**@}*/

/**
 * @defgroup RateGroup angular rate representations
 * @{
 */
#define RATE_I 1<<0
#define RATE_F 1<<1
/**@}*/

/**
 * @defgroup WindAirGroup wind- and airspeed representations
 * @{
 */
#define WINDSPEED_I 1<<0
#define AIRSPEED_I  1<<1
#define WINDSPEED_F 1<<2
#define AIRSPEED_F  1<<3
/**@}*/


/**
 * @brief structure holding vehicle state data
 */
struct State {

  /** @addtogroup PosGroup
   *  @{ */
  /**
   * @brief holds the status bits for all position representations
   * @details When the corresponding bit is one the representation
   * is already computed. */
  uint8_t pos_status;

  /**
   * @brief position in EarthCenteredEarthFixed coordinates
   * @details Units: centimeters */
  struct EcefCoor_i ecef_pos_i;

  /**
   * @brief position in Latitude, Longitude and Altitude
   * @details Units lat,lon: radians*1e7
   * Units alt: centimeters above MSL
   */
  struct LlaCoor_i lla_pos_i;

  /**
   * @brief definition of the local (flat earth) coordinate system
   * @details Defines the origin of the local coordinate system
   * in ECEF and LLA coordinates and the roation matrix from
   * ECEF to local frame */
  struct LtpDef_i ned_origin_i;

  /**
   * @brief true if local int coordinate frame is initialsed */
  bool_t ned_initialised_i;

  /**
   * @brief position in North East Down coordinates
   * @details @details with respect to ned_origin_i (flat earth)
   * Units: m in BFP with INT32_POS_FRAC */
  struct NedCoor_i ned_pos_i;

  /**
   * @brief position in UTM coordinates
   * @details Units x,y: meters.
   * Units z: meters above MSL */
  struct FloatVect3 utm_pos_f;

  /**
   * @brief UTM zone number */
  uint8_t utm_zone_f;

  /**
   * @brief altitude above ground level
   * @details Unit: meters */
  float alt_agl_f;

  /**
   * @brief position in Latitude, Longitude and Altitude
   * @details Units lat,lon: radians
   * Units alt: meters above MSL
   */
  struct LlaCoor_f lla_pos_f;

  /**
   * @brief position in EarthCenteredEarthFixed coordinates
   * @details Units: meters */
  struct EcefCoor_f ecef_pos_f;

  /**
   * @brief definition of the local (flat earth) coordinate system
   * @details Defines the origin of the local coordinate system
   * in ECEF and LLA coordinates and the roation matrix from
   * ECEF to local frame */
  struct LtpDef_f ned_origin_f;

  /**
   * @brief true if local float coordinate frame is initialsed */
  bool_t ned_initialised_f;

  /**
   * @brief position in North East Down coordinates
   * @details @details with respect to ned_origin_i (flat earth)
   * Units: meters */
  struct NedCoor_f ned_pos_f;
  /** @}*/


  /** @addtogroup SpeedGroup
   *  @{ */
  /**
   * @brief holds the status bits for all ground speed representations
   * @details When the corresponding bit is one the representation
   * is already computed. */
  uint8_t speed_status;

  /**
   * @brief speed in EarthCenteredEarthFixed coordinates
   * @details Units: m/s in BFP with INT32_SPEED_FRAC */
  struct EcefCoor_i ecef_speed_i;

  /**
   * @brief speed in North East Down coordinates
   * @details Units: m/s in BFP with INT32_SPEED_FRAC */
  struct NedCoor_i ned_speed_i;

  /**
   * @brief norm of horizontal ground speed
   * @details Units: m/s in BFP with INT32_SPEED_FRAC */
  int32_t h_speed_norm_i;

  /**
   * @brief dir of horizontal ground speed
   * @details Units: rad in BFP with INT32_ANGLE_FRAC */
  int32_t h_speed_dir_i;

  /**
   * @brief speed in EarthCenteredEarthFixed coordinates
   * @details Units: m/s */
  struct EcefCoor_f ecef_speed_f;

  /**
   * @brief speed in North East Down coordinates
   * @details Units: m/s */
  struct NedCoor_f ned_speed_f;

  /**
   * @brief norm of horizontal ground speed
   * @details Units: m/s */
  float h_speed_norm_f;

  /**
   * @brief dir of horizontal ground speed
   * @details Units: rad (clockwise, zero=north)*/
  float h_speed_dir_f;
  /** @}*/


  /** @addtogroup AccelGroup
   *  @{ */
  /**
   * @brief holds the status bits for all acceleration representations
   * @details When the corresponding bit is one the representation
   * is already computed. */
  uint8_t accel_status;

  /**
   * @brief acceleration in North East Down coordinates
   * @details @details Units: m/s^2 in BFP with INT32_ACCEL_FRAC */
  struct NedCoor_i ned_accel_i;

  /**
   * @brief acceleration in EarthCenteredEarthFixed coordinates
   * @details Units: m/s^2 in BFP with INT32_ACCEL_FRAC */
  struct EcefCoor_i ecef_accel_i;

  /**
   * @brief acceleration in North East Down coordinates
   * @details Units: m/s^2 */
  struct NedCoor_f ned_accel_f;

  /**
   * @brief acceleration in EarthCenteredEarthFixed coordinates
   * @details Units: m/s^2 */
  struct EcefCoor_f ecef_accel_f;
  /** @}*/


  /** @addtogroup AttGroup
   *  @{ */
  /**
   * @brief holds the status bits for all attitude representations
   * @details When the corresponding bit is one the representation
   * is already computed. */
  uint8_t att_status;

  /**
   * @brief attitude as quaternion
   * @details Specifies rotation from local NED frame to body frame.
   * Units: INT32_QUAT_FRAC
   *
   * @code
   * struct Int32Vect3 body_accel;
   * INT32_QUAT_VMULT(body_accel, stateGetNedToBodyQuat_i(), stateGetAccelNed_i());
   * @endcode
   */
  struct Int32Quat ned_to_body_quat_i;

  /**
   * @brief attitude in zyx euler angles
   * @details Specifies rotation from local NED frame to body frame.
   * Units: rad in BFP with INT32_ANGLE_FRAC */
  struct Int32Eulers ned_to_body_eulers_i;

  /**
   * @brief attitude rotation matrix
   * @details Specifies rotation from local NED frame to body frame.
   * Units: rad in BFP with INT32_TRIG_FRAC */
  struct Int32RMat   ned_to_body_rmat_i;

   /**
   * @brief attitude as quaternion
   * @details Specifies rotation from local NED frame to body frame.
   * Units: unit length
   *
   * @code
   * struct FloatVect3 body_accel;
   * FLOAT_QUAT_VMULT(body_accel, stateGetNedToBodyQuat_f(), stateGetAccelNed_f());
   * @endcode
   */
  struct FloatQuat   ned_to_body_quat_f;

  /**
   * @brief attitude in zyx euler angles
   * @details Specifies rotation from local NED frame to body frame.
   * Units: rad */
  struct FloatEulers ned_to_body_eulers_f;

  /**
   * @brief attitude rotation matrix
   * @details Specifies rotation from local NED frame to body frame.
   * Units: rad */
  struct FloatRMat   ned_to_body_rmat_f;
  /** @}*/


  /** @addtogroup RateGroup
   *  @{ */
  /**
   * @brief holds the status bits for all angular rate representations
   * @details When the corresponding bit is one the representation
   * is already computed. */
  uint8_t rate_status;

  /**
   * @brief angular rates in body frame
   * @details Units: rad/s^2 in BFP with INT32_RATE_FRAC */
  struct Int32Rates  body_rates_i;

  /**
   * @brief angular rates in body frame
   * @details Units: rad/s^2 */
  struct FloatRates  body_rates_f;
  /** @}*/


  /** @addtogroup WindAirGroup
   *  @{ */
  /**
   * @brief holds the status bits for all wind- and airspeed representations
   * @details When the corresponding bit is one the representation
   * is already computed. */
  uint8_t wind_air_status;

  /**
   * @brief horizontal windspeed in north/east
   * @details Units: m/s in BFP with INT32_SPEED_FRAC */
  struct Int32Vect2 h_windspeed_i;

  /**
   * @brief norm of horizontal ground speed
   * @details Units: m/s in BFP with INT32_SPEED_FRAC */
  int32_t airspeed_i;

  /**
   * @brief horizontal windspeed
   * @details Units: m/s with x=north, y=east */
  struct FloatVect2 h_windspeed_f;

  /**
   * @brief norm of horizontal ground speed
   * @details Units: m/s */
  float airspeed_f;
  /** @}*/

};

extern struct State state;



/*******************************************************************************
 *                                                                             *
 * Set and Get functions for the POSITION representations                   *
 *                                                                             *
 ******************************************************************************/
/** @addtogroup PosGroup
 *  @{ */

/************* declaration of transformation functions ************/
extern void stateCalcPositionEcef_i(void);
extern void stateCalcPositionNed_i(void);
extern void stateCalcPositionLla_i(void);
extern void stateCalcPositionEcef_f(void);
extern void stateCalcPositionNed_f(void);
extern void stateCalcPositionLla_f(void);

/************************ Set functions ****************************/

/** @brief Set position from ECEF coordinates (int). */
static inline void stateSetPositionEcef_i(struct EcefCoor_i* ecef_pos) {
  INT32_VECT3_COPY(state.ecef_pos_i, *ecef_pos);
  /* clear bits for all position representations and only set the new one */
  state.pos_status = (1 << POS_ECEF_I);
}

/** @brief Set position from local NED coordinates (int). */
static inline void stateSetPositionNed_i(struct NedCoor_i* ned_pos) {
  INT32_VECT3_COPY(state.ned_pos_i, *ned_pos);
  /* clear bits for all position representations and only set the new one */
  state.pos_status = (1 << POS_NED_I);
}

/** @brief Set position from LLA coordinates (int). */
static inline void stateSetPositionLla_i(struct LlaCoor_i* lla_pos) {
  LLA_COPY(state.lla_pos_i, *lla_pos);
  /* clear bits for all position representations and only set the new one */
  state.pos_status = (1 << POS_LLA_I);
}

/** @brief Set position from UTM coordinates (float). */
static inline void stateSetPositionUtm_f(struct FloatVect3* utm_pos) {
  //TODO utm zone??
  VECT3_COPY(state.utm_pos_f, *utm_pos);
  /* clear bits for all position representations and only set the new one */
  state.pos_status = (uint8_t)(1 << POS_UTM_F);
}

/** @brief Set position from ECEF coordinates (float). */
static inline void stateSetPositionEcef_f(struct EcefCoor_f* ecef_pos) {
  VECT3_COPY(state.ecef_pos_f, *ecef_pos);
  /* clear bits for all position representations and only set the new one */
  state.pos_status = (1 << POS_ECEF_F);
}

/** @brief Set position from local NED coordinates (float). */
static inline void stateSetPositionNed_f(struct NedCoor_f* ned_pos) {
  VECT3_COPY(state.ned_pos_f, *ned_pos);
  /* clear bits for all position representations and only set the new one */
  state.pos_status = (1 << POS_NED_F);
}

/** @brief Set position from LLA coordinates (float). */
static inline void stateSetPositionLla_f(struct LlaCoor_f* lla_pos) {
  LLA_COPY(state.lla_pos_f, *lla_pos);
  /* clear bits for all position representations and only set the new one */
  state.pos_status = (1 << POS_LLA_F);
}

/************************ Get functions ****************************/

/** @brief Get position in ECEF coordinates (int). */
static inline struct EcefCoor_i stateGetPositionEcef_i(void) {
  if (!bit_is_set(state.pos_status, POS_ECEF_I))
    stateCalcPositionEcef_i();
  return state.ecef_pos_i;
}

/** @brief Get position in local NED coordinates (int). */
static inline struct NedCoor_i stateGetPositionNed_i(void) {
  if (!bit_is_set(state.pos_status, POS_NED_I))
    stateCalcPositionNed_i();
  return state.ned_pos_i;
}

/** @brief Get position in LLA coordinates (int). */
static inline struct LlaCoor_i stateGetPositionLla_i(void) {
  if (!bit_is_set(state.pos_status, POS_LLA_I))
    stateCalcPositionLla_i();
  return state.lla_pos_i;
}

/** @brief Get position in UTM coordinates (float). */
//static inline struct FloatVect3 stateGetPositionUtm_f(void);

/** @brief Get position in ECEF coordinates (float). */
static inline struct EcefCoor_f stateGetPositionEcef_f(void) {
  if (!bit_is_set(state.pos_status, POS_ECEF_F))
    stateCalcPositionEcef_f();
  return state.ecef_pos_f;
}

/** @brief Get position in local NED coordinates (float). */
static inline struct NedCoor_f stateGetPositionNed_f(void) {
  if (!bit_is_set(state.pos_status, POS_NED_F))
    stateCalcPositionNed_f();
  return state.ned_pos_f;
}

/** @brief Get position in LLA coordinates (float). */
static inline struct LlaCoor_f stateGetPositionLla_f(void) {
  if (!bit_is_set(state.pos_status, POS_LLA_F))
    stateCalcPositionLla_f();
  return state.lla_pos_f;
}

/** @}*/



/******************************************************************************
 *                                                                            *
 * Set and Get functions for the SPEED representations                        *
 *                                                                            *
 *****************************************************************************/
/** @addtogroup SpeedGroup
 *  @{ */

/************* declaration of transformation functions ************/
extern void stateCalcSpeedNed_i(void);
extern void stateCalcSpeedEcef_i(void);
extern void stateCalcHorizontalSpeedNorm_i(void);
extern void stateCalcHorizontalSpeedDir_i(void);
extern void stateCalcSpeedNed_f(void);
extern void stateCalcSpeedEcef_f(void);
extern void stateCalcHorizontalSpeedNorm_f(void);
extern void stateCalcHorizontalSpeedDir_f(void);

/************************ Set functions ****************************/

/** @brief Set ground speed in local NED coordinates (int). */
static inline void stateSetSpeedNed_i(struct NedCoor_i* ned_speed) {
  INT32_VECT3_COPY(state.ned_speed_i, *ned_speed);
  /* clear bits for all speed representations and only set the new one */
  state.speed_status = (1 << SPEED_NED_I);
}

/** @brief Set ground speed in ECEF coordinates (int). */
static inline void stateSetSpeedEcef_i(struct EcefCoor_i* ecef_speed) {
  INT32_VECT3_COPY(state.ecef_speed_i, *ecef_speed);
  /* clear bits for all speed representations and only set the new one */
  state.speed_status = (1 << SPEED_ECEF_I);
}

/** @brief Set ground speed in local NED coordinates (float). */
static inline void stateSetSpeedNed_f(struct NedCoor_f* ned_speed) {
  VECT3_COPY(state.ned_speed_f, *ned_speed);
  /* clear bits for all speed representations and only set the new one */
  state.speed_status = (1 << SPEED_NED_F);
}

/** @brief Set ground speed in ECEF coordinates (float). */
static inline void stateSetSpeedEcef_f(struct EcefCoor_f* ecef_speed) {
  VECT3_COPY(state.ecef_speed_f, *ecef_speed);
  /* clear bits for all speed representations and only set the new one */
  state.speed_status = (1 << SPEED_ECEF_F);
}

/************************ Get functions ****************************/

/** @brief Get ground speed in local NED coordinates (int). */
static inline struct NedCoor_i stateGetSpeedNed_i(void) {
  if (!bit_is_set(state.speed_status, SPEED_NED_I))
    stateCalcSpeedNed_i();
  return state.ned_speed_i;
}

/** @brief Get ground speed in ECEF coordinates (int). */
static inline struct EcefCoor_i stateGetSpeedEcef_i(void) {
  if (!bit_is_set(state.speed_status, SPEED_ECEF_I))
    stateCalcSpeedEcef_i();
  return state.ecef_speed_i;
}

/** @brief Get norm of horizontal ground speed (int). */
static inline int32_t stateGetHorizontalSpeedNorm_i(void) {
  if (!bit_is_set(state.speed_status, SPEED_HNORM_I))
    stateCalcHorizontalSpeedNorm_i();
  return state.h_speed_norm_i;
}

/** @brief Get dir of horizontal ground speed (int). */
static inline int32_t stateGetHorizontalSpeedDir_i(void) {
  if (!bit_is_set(state.speed_status, SPEED_HDIR_I))
    stateCalcHorizontalSpeedDir_i();
  return state.h_speed_dir_i;
}

/** @brief Get ground speed in local NED coordinates (float). */
static inline struct NedCoor_f stateGetSpeedNed_f(void) {
  if (!bit_is_set(state.speed_status, SPEED_NED_F))
    stateCalcSpeedNed_f();
  return state.ned_speed_f;
}

/** @brief Get ground speed in ECEF coordinates (float). */
static inline struct EcefCoor_f stateGetSpeedEcef_f(void) {
  if (!bit_is_set(state.speed_status, SPEED_ECEF_F))
    stateCalcSpeedEcef_f();
  return state.ecef_speed_f;
}

/** @brief Get norm of horizontal ground speed (float). */
static inline float stateGetHorizontalSpeedNorm_f(void) {
  if (!bit_is_set(state.speed_status, SPEED_HNORM_F))
    stateCalcHorizontalSpeedNorm_f();
  return state.h_speed_norm_f;
}

/** @brief Get dir of horizontal ground speed (float). */
static inline float stateGetHorizontalSpeedDir_f(void) {
  if (!bit_is_set(state.speed_status, SPEED_HDIR_F))
    stateCalcHorizontalSpeedDir_f();
  return state.h_speed_dir_f;
}
/** @}*/



/******************************************************************************
 *                                                                            *
 * Set and Get functions for the ACCELERATION representations                 *
 *                                                                            *
 *****************************************************************************/
/** @addtogroup AccelGroup
 *  @{ */

/************* declaration of transformation functions ************/
extern void stateCalcAccelNed_i(void);
extern void stateCalcAccelEcef_i(void);
extern void stateCalcAccelNed_f(void);
extern void stateCalcAccelEcef_f(void);

/************************ Set functions ****************************/

/** @brief Set acceleration in NED coordinates (int). */
static inline void stateSetAccelNed_i(struct NedCoor_i* ned_accel) {
  INT32_VECT3_COPY(state.ned_accel_i, *ned_accel);
  /* clear bits for all accel representations and only set the new one */
  state.accel_status = (1 << ACCEL_NED_I);
}

/** @brief Set acceleration in ECEF coordinates (int). */
static inline void stateSetAccelEcef_i(struct EcefCoor_i* ecef_accel) {
  INT32_VECT3_COPY(state.ecef_accel_i, *ecef_accel);
  /* clear bits for all accel representations and only set the new one */
  state.accel_status = (1 << ACCEL_ECEF_I);
}

/** @brief Set acceleration in NED coordinates (float). */
static inline void stateSetAccelNed_f(struct NedCoor_f* ned_accel) {
  VECT3_COPY(state.ned_accel_f, *ned_accel);
  /* clear bits for all accel representations and only set the new one */
  state.accel_status = (1 << ACCEL_NED_F);
}

/** @brief Set acceleration in ECEF coordinates (float). */
static inline void stateSetAccelEcef_f(struct EcefCoor_f* ecef_accel) {
  VECT3_COPY(state.ecef_accel_f, *ecef_accel);
  /* clear bits for all accel representations and only set the new one */
  state.accel_status = (1 << ACCEL_ECEF_F);
}

/************************ Get functions ****************************/

/** @brief Get acceleration in NED coordinates (int). */
static inline struct NedCoor_i stateGetAccelNed_i(void) {
  if (!bit_is_set(state.accel_status, ACCEL_NED_I))
    stateCalcAccelNed_i();
  return state.ned_accel_i;
}

/** @brief Get acceleration in ECEF coordinates (int). */
static inline struct EcefCoor_i stateGetAccelEcef_i(void) {
  if (!bit_is_set(state.accel_status, ACCEL_ECEF_I))
    stateCalcAccelEcef_i();
  return state.ecef_accel_i;
}

/** @brief Get acceleration in NED coordinates (float). */
static inline struct NedCoor_f stateGetAccelNed_f(void) {
  if (!bit_is_set(state.accel_status, ACCEL_NED_F))
    stateCalcAccelNed_f();
  return state.ned_accel_f;
}

/** @brief Get acceleration in ECEF coordinates (float). */
static inline struct EcefCoor_f stateGetAccelEcef_f(void) {
  if (!bit_is_set(state.accel_status, ACCEL_ECEF_F))
    stateCalcAccelEcef_f();
  return state.ecef_accel_f;
}
/** @}*/



/******************************************************************************
 *                                                                            *
 * Set and Get functions for the ATTITUDE representations                     *
 *                                                                            *
 *****************************************************************************/
/** @addtogroup AttGroup
 *  @{ */

/************* declaration of transformation functions ************/
extern void stateCalcNedToBodyQuat_i(void);
extern void stateCalcNedToBodyRMat_i(void);
extern void stateCalcNedToBodyEulers_i(void);
extern void stateCalcNedToBodyQuat_f(void);
extern void stateCalcNedToBodyRMat_f(void);
extern void stateCalcNedToBodyEulers_f(void);

/************************ Set functions ****************************/

/** @brief Set vehicle body attitude from quaternion (int). */
static inline void stateSetNedToBodyQuat_i(struct Int32Quat* ned_to_body_quat) {
  QUAT_COPY(state.ned_to_body_quat_i, *ned_to_body_quat);
  /* clear bits for all attitude representations and only set the new one */
  state.att_status = (1 << ATT_QUAT_I);
}

/** @brief Set vehicle body attitude from rotation matrix (int). */
static inline void stateSetNedToBodyRMat_i(struct Int32RMat* ned_to_body_rmat) {
  RMAT_COPY(state.ned_to_body_rmat_i, *ned_to_body_rmat);
  /* clear bits for all attitude representations and only set the new one */
  state.att_status = (1 << ATT_RMAT_I);
}

/** @brief Set vehicle body attitude from euler angles (int). */
static inline void stateSetNedToBodyEulers_i(struct Int32Eulers* ned_to_body_eulers) {
  EULERS_COPY(state.ned_to_body_eulers_i, *ned_to_body_eulers);
  /* clear bits for all attitude representations and only set the new one */
  state.att_status = (1 << ATT_EULER_I);
}

/** @brief Set vehicle body attitude from quaternion (float). */
static inline void stateSetNedToBodyQuat_f(struct FloatQuat* ned_to_body_quat) {
  QUAT_COPY(state.ned_to_body_quat_f, *ned_to_body_quat);
  /* clear bits for all attitude representations and only set the new one */
  state.att_status = (1 << ATT_QUAT_F);
}

/** @brief Set vehicle body attitude from rotation matrix (float). */
static inline void stateSetNedToBodyRMat_f(struct FloatRMat* ned_to_body_rmat) {
  RMAT_COPY(state.ned_to_body_rmat_f, *ned_to_body_rmat);
  /* clear bits for all attitude representations and only set the new one */
  state.att_status = (1 << ATT_RMAT_F);
}

/** @brief Set vehicle body attitude from euler angles (float). */
static inline void stateSetNedToBodyEulers_f(struct FloatEulers* ned_to_body_eulers) {
  EULERS_COPY(state.ned_to_body_eulers_f, *ned_to_body_eulers);
  /* clear bits for all attitude representations and only set the new one */
  state.att_status = (1 << ATT_EULER_F);
}

/************************ Get functions ****************************/

/** @brief Get vehicle body attitude quaternion (int). */
static inline struct Int32Quat stateGetNedToBodyQuat_i(void) {
  if (!bit_is_set(state.att_status, ATT_QUAT_I))
    stateCalcNedToBodyQuat_i();
  return state.ned_to_body_quat_i;
}

/** @brief Get vehicle body attitude rotation matrix (int). */
static inline struct Int32RMat stateGetNedToBodyRMat_i(void) {
  if (!bit_is_set(state.att_status, ATT_RMAT_I))
    stateCalcNedToBodyRMat_i();
  return state.ned_to_body_rmat_i;
}

/** @brief Get vehicle body attitude euler angles (int). */
static inline struct Int32Eulers stateGetNedToBodyEulers_i(void) {
  if (!bit_is_set(state.att_status, ATT_EULER_I))
    stateCalcNedToBodyEulers_i();
  return state.ned_to_body_eulers_i;
}

/** @brief Get vehicle body attitude quaternion (float). */
static inline struct FloatQuat stateGetNedToBodyQuat_f(void) {
  if (!bit_is_set(state.att_status, ATT_QUAT_F))
    stateCalcNedToBodyQuat_f();
  return state.ned_to_body_quat_f;
}

/** @brief Get vehicle body attitude rotation matrix (float). */
static inline struct FloatRMat stateGetNedToBodyRMat_f(void) {
  if (!bit_is_set(state.att_status, ATT_RMAT_F))
    stateCalcNedToBodyRMat_f();
  return state.ned_to_body_rmat_f;
}

/** @brief Get vehicle body attitude euler angles (float). */
static inline struct FloatEulers stateGetNedToBodyEulers_f(void) {
  if (!bit_is_set(state.att_status, ATT_EULER_F))
    stateCalcNedToBodyEulers_f();
  return state.ned_to_body_eulers_f;
}
/** @}*/



/******************************************************************************
 *                                                                            *
 * Set and Get functions for the ANGULAR RATE representations                 *
 *                                                                            *
 *****************************************************************************/
/** @addtogroup RateGroup
 *  @{ */

/************* declaration of transformation functions ************/
extern void stateCalcBodyRates_i(void);
extern void stateCalcBodyRates_f(void);

/************************ Set functions ****************************/

/** @brief Set vehicle body angular rate (int). */
static inline void stateSetBodyRates_i(struct Int32Rates* body_rate) {
  RATES_COPY(state.body_rates_i, *body_rate);
  /* clear bits for all attitude representations and only set the new one */
  state.rate_status = (1 << RATE_I);
}

/** @brief Set vehicle body angular rate (float). */
static inline void stateSetBodyRates_f(struct FloatRates* body_rate) {
  RATES_COPY(state.body_rates_f, *body_rate);
  /* clear bits for all attitude representations and only set the new one */
  state.rate_status = (1 << RATE_F);
}

/************************ Get functions ****************************/

/** @brief Get vehicle body angular rate (int). */
static inline struct Int32Rates stateGetBodyRates_i(void) {
  if (!bit_is_set(state.rate_status, RATE_I))
    stateCalcBodyRates_i();
  return state.body_rates_i;
}

/** @brief Get vehicle body angular rate (float). */
static inline struct FloatRates stateGetBodyRates_f(void) {
  if (!bit_is_set(state.rate_status, RATE_F))
    stateCalcBodyRates_f();
  return state.body_rates_f;
}

/** @}*/



/******************************************************************************
 *                                                                            *
 * Set and Get functions for the WIND- AND AIRSPEED representations           *
 *                                                                            *
 *****************************************************************************/
/** @addtogroup WindAirGroup
 *  @{ */

/************* declaration of transformation functions ************/
extern void stateCalcHorizontalWindspeed_i(void);
extern void stateCalcAirspeed_i(void);
extern void stateCalcHorizontalWindspeed_f(void);
extern void stateCalcAirspeed_f(void);

/************************ Set functions ****************************/

/** @brief Set horizontal windspeed (int). */
static inline void stateSetHorizontalWindspeed_i(struct Int32Vect2* h_windspeed) {
  VECT2_COPY(state.h_windspeed_i, *h_windspeed);
  /* clear bits for all windspeed representations and only set the new one */
  ClearBit(state.wind_air_status, WINDSPEED_F);
  SetBit(state.wind_air_status, WINDSPEED_I);
}

/** @brief Set airspeed (int). */
static inline void stateSetAirspeed_i(int32_t* airspeed) {
  state.airspeed_i = *airspeed;
  /* clear bits for all windspeed representations and only set the new one */
  ClearBit(state.wind_air_status, AIRSPEED_F);
  SetBit(state.wind_air_status, AIRSPEED_I);
}

/** @brief Set horizontal windspeed (float). */
static inline void stateSetHorizontalWindspeed_f(struct FloatVect2* h_windspeed) {
  VECT2_COPY(state.h_windspeed_f, *h_windspeed);
  /* clear bits for all windspeed representations and only set the new one */
  ClearBit(state.wind_air_status, WINDSPEED_I);
  SetBit(state.wind_air_status, WINDSPEED_F);
}

/** @brief Set airspeed (float). */
static inline void stateSetAirspeed_f(float* airspeed) {
  state.airspeed_f = *airspeed;
  /* clear bits for all windspeed representations and only set the new one */
  ClearBit(state.wind_air_status, AIRSPEED_I);
  SetBit(state.wind_air_status, AIRSPEED_F);
}

/************************ Get functions ****************************/

/** @brief Get horizontal windspeed (int). */
static inline struct Int32Vect2 stateGetHorizontalWindspeed_i(void) {
  if (!bit_is_set(state.wind_air_status, WINDSPEED_I))
    stateCalcHorizontalWindspeed_i();
  return state.h_windspeed_i;
}

/** @brief Get airspeed (int). */
static inline int32_t stateGetAirspeed_i(void) {
  if (!bit_is_set(state.wind_air_status, AIRSPEED_I))
    stateCalcAirspeed_i();
  return state.airspeed_i;
}

/** @brief Get horizontal windspeed (float). */
static inline struct FloatVect2 stateGetHorizontalWindspeed_f(void) {
  if (!bit_is_set(state.wind_air_status, WINDSPEED_F))
    stateCalcHorizontalWindspeed_f();
  return state.h_windspeed_f;
}

/** @brief Get airspeed (float). */
static inline float stateGetAirspeed_f(void) {
  if (!bit_is_set(state.wind_air_status, AIRSPEED_F))
    stateCalcAirspeed_f();
  return state.airspeed_f;
}

/** @}*/


#endif /* STATE_H */
