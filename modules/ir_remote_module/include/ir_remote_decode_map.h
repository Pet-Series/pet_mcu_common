#ifndef _IRREMOTELIB_H
#define _IRREMOTELIB_H
// Consumer IR, Consumer Infrared (CIR) codes
//
// Key to code mapping:
//      Varies from remote control to remote control.
//      In many cases, the codes sent may have more to do with the row and column positions on the remote than any unified plan.
//
// For more information on key codes and the CIR protocol, please see...
//      https://irforum.analysir.com/
//      https://github.com/z3t0/Arduino-IRremote
//

// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
// Sample IR-codes used by (RC) HP TSGH-IR01 SW rev: A (HP WINDOWS PC MEDIA)
// IR_decode_results.decode_type = "RC6"
//    "RC6" & "RC5" standards are dev. by Philips
//    "*_t1" = Toggle bit... when the key is pressed for the first time.
//    "*_t2" = Toggle bit... when the key is hold down -> repeating keyes.
//    For more details see https://www.sbprojects.net/knowledge/ir/rc6.php
// IR_decode_results.value = See key codes below...

#define IR_RC6_OnOff_t1     0x800F040C
#define IR_RC6_OnOff_t2     0x800F840C
#define IR_RC6_Up_t1        0x800F041E
#define IR_RC6_Up_t2        0x800F841E
#define IR_RC6_Left_t1      0x800F0420
#define IR_RC6_Left_t2      0x800F8420
#define IR_RC6_Right_t1     0x800F0421
#define IR_RC6_Right_t2     0x800F8421
#define IR_RC6_Down_t1      0x800F041F
#define IR_RC6_Down_t2      0x800F841F
#define IR_RC6_Play_t1      0x800F0416
#define IR_RC6_Play_t2      0x800F8416
#define IR_RC6_Stop_t1      0x800F0419
#define IR_RC6_Stop_t2      0x800F8419
#define IR_RC6_Pause_t1     0x800F0418
#define IR_RC6_Pause_t2     0x800F8418
#define IR_RC6_FFwd_t1      0x800F0414
#define IR_RC6_FFwd_t2      0x800F8414
#define IR_RC6_Rewind_t1    0x800F0415
#define IR_RC6_Rewind_t2    0x800F8415
// TODO: IR_RC6_Eject
// TODO: IR_RC6_Record  0x800F0417 / 0x800F8417
#define IR_RC6_VolPlus_t1   0x800F0410
#define IR_RC6_VolPlus_t2   0x800F8410
#define IR_RC6_VolMinus_t1  0x800F0411
#define IR_RC6_VolMinus_t2  0x800F8411
// TODO: IR_RC6_ChPlus
// TODO: IR_RC6_ChMinus
#define IR_RC6_Mute_t1      0x800F040E
#define IR_RC6_Mute_t2      0x800F840E
#define IR_RC6_Ok_t1        0x800F0422
#define IR_RC6_Ok_t2        0x800F8422
#define IR_RC6_Win_t1       0x800F040D
#define IR_RC6_Win_t2       0x800F840D
#define IR_RC6_Back_t1      0x800F0423 // (KEY_BACK_Repeatedly)... Note reverse mapping
#define IR_RC6_Back_t2      0x800F8423 //(KEY_BACK_Pressed)... Note reverse mapping
#define IR_RC6_Menu_t1      0x800F0426
#define IR_RC6_Menu_t2      0x800F8426
#define IR_RC6_Info_t1      0x800F040F
#define IR_RC6_Info_t2      0x800F840F
#define IR_RC6_0_t1         0x800F0400 // (KEY_NUMERIC_0_Pressed)
#define IR_RC6_0_t2         0x800F8400 // (KEY_NUMERIC_0_Repeatedly)
#define IR_RC6_1_t1         0x800F0401
#define IR_RC6_1_t2         0x800F8401
#define IR_RC6_2_t1         0x800F0402
#define IR_RC6_2_t2         0x800F8402
#define IR_RC6_3_t1         0x800F0403
#define IR_RC6_3_t2         0x800F8403
#define IR_RC6_4_t1         0x800F0404
#define IR_RC6_4_t2         0x800F8404
#define IR_RC6_5_t1         0x800F0405
#define IR_RC6_5_t2         0x800F8405
#define IR_RC6_6_t1         0x800F0406
#define IR_RC6_6_t2         0x800F8406
#define IR_RC6_7_t1         0x800F0407
#define IR_RC6_7_t2         0x800F8407
#define IR_RC6_8_t1         0x800F0408
#define IR_RC6_8_t2         0x800F8408
#define IR_RC6_9_t1         0x800F0409 // (KEY_NUMERIC_9_Pressed)
#define IR_RC6_9_t2         0x800F8409 // (KEY_NUMERIC_9_Repeatedly)
// TODO: IR_RC6_Star
// TODO: IR_RC6_Hash
#define IR_RC6_Clear_t1     0x800F040A  // (KEY_NUMERIC_Clear_Pressed)
#define IR_RC6_Clear_t2     0x800F840A  // (KEY_NUMERIC_Clear_Repeatedly)
#define IR_RC6_Enter_t1     0x800F040B  // (KEY_NUMERIC_Enter_Pressed)
#define IR_RC6_Enter_t2     0x800F840B  // (KEY_NUMERIC_Enter_Repeatedly)
#define IR_RC6_Red_t1       0x800F045B  // (KEY_Red_Pressed)
#define IR_RC6_Red_t2       0x800F845B  // (KEY_Red_Repeatedly)
#define IR_RC6_Green_t1     0x800F045C  // (KEY_Green_Pressed)
#define IR_RC6_Green_t2     0x800F845C  // (KEY_Green_Repeatedly)
#define IR_RC6_Yellow_t1    0x800F045D  // (KEY_Yellow_Pressed)
#define IR_RC6_Yellow_t2    0x800F845D  // (KEY_Yellow_Repeatedly)
#define IR_RC6_Blue_t1      0x800F045E  // (KEY_Blue_Pressed)
#define IR_RC6_Blue_t2      0x800F845E  // (KEY_Blue_Repeatedly)
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
// Sample IR-codes used by Japanese brands, like NEC
// IR_decode_results.decode_type = "NEC"
//    "NEC" standards are dev. by NEC (and adopted for most Japanese brands)
//    For more details see https://www.sbprojects.net/knowledge/ir/nec.php
// IR_decode_results.decode_type = "NEC"
// IR_decode_results.value = See key codes below...
#define IR_NEC_Repeat       0xFFFFFFFF
#define IR_NEC_OnOff        0xFFA25D   
#define IR_NEC_PlayPause    0xFF22DD   
#define IR_NEC_FFwd         0xFFC23D   
#define IR_NEC_Rewind       0xFF02FD   
#define IR_NEC_VolPlus      0xFF906F   
#define IR_NEC_VolMinus     0xFFA857   
#define IR_NEC_Mute         0xFFE21D   
#define IR_NEC_Mode         0xFF629D   
#define IR_NEC_0            0xFF6897   // (KEY_NUMERIC_0)
#define IR_NEC_1            0xFF30CF   // (KEY_NUMERIC_1)
#define IR_NEC_2            0xFF18E7   
#define IR_NEC_3            0xFF7A85   
#define IR_NEC_4            0xFF10EF   
#define IR_NEC_5            0xFF38C7   
#define IR_NEC_6            0xFF5AA5   
#define IR_NEC_7            0xFF42BD   
#define IR_NEC_8            0xFF4AB5   
#define IR_NEC_9            0xFF52AD   // (KEY_NUMERIC_9)

#endif