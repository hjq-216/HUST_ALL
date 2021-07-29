PUBLIC   NEWLINE
PUBLIC   ADDRESS_TEMP
EXTRN    FUNC6:FAR
.386
NAME LAB03

CALCULATOR MACRO A
         MOV DI,OFFSET A
         ADD DI,10
         MOV AH,5[DI]
         MOV AL,7[DI]
         SUB AH,AL
         CMP AH,0
         JZ AUTH_FAIL1D
         MOV AX, WORD PTR 3[DI]
         MOV DL, BYTE PTR [DI]
         MOV DH, 0
         MUL DX
         MOV CX, 10
         DIV CX
         MOV CX,AX
         MOV AX, 1[DI]
         MOV DX,128
         MUL DX
         MOV DX,0
         DIV CX
         MOV CX, AX
         MOV AX, WORD PTR 7[DI]
         MOV DX,64
         MUL DX
         MOV DX,0
         DIV WORD PTR 5[DI]
         ADD AX, CX
         MOV WORD PTR 9[DI],AX 
         ENDM

STACK   SEGMENT  PARA STACK 'STACK'
        DB 200 DUP(0)
STACK   ENDS

DATA SEGMENT USE16  PARA PUBLIC 'A1'
    BNAME DB  'HUANG JUNQI',0
    BPASS DB  '12345',0
    AUTH DB 0
    GOOD DW 0,'$'
    N EQU 30
    M EQU 1020
    SNAME DB 'SHOP',0,'$'
    GA1 DB 'PEN',6 DUP(0),'$',10
    DW 35, 56 ,70,25 ,?
    GA2 DB 'BOOK',5 DUP(0),'$',9
    DW 12,30,25,5,?
    GA3 DB 'BAG',6 DUP(0),'$',9
    DW 10,20,1000,0,?
    GAN DB N-3 DUP('TEMPVALUE',8,15,0,20,0,30,0,2,0,?,?)
    IN_NAME DB 20,20 DUP(0)
    IN_PWD DB 10,10 DUP(0)
    OPTION1 DB 2 DUP(0),'$'
    VIEWER_HINT1    DB 'HUANG JUNQI','$'
    VIEWER_HINT2    DB 'CUSTOMER','$'
    GOOD_HINT1      DB 'PEN','$'
    GOOD_HINT3      DB 'BAG','$'
    GOOD_HINT2      DB 'BOOK','$'
    MENU_HINT1      DB '1.SIGN IN','$'
    MENU_HINT2      DB '2.SERCH GOODS','$'
    MENU_HINT3      DB '3.ORDER','$'
    MENU_HINT4      DB '4.CAULATE','$'
    MENU_HINT5      DB '5.SORT','$'
    MENU_HINT6      DB '6.REVISE','$'
    MENU_HINT7      DB '7.CHANGE EXPERIMENT ','$'
    MENU_HINT8      DB '8.SHOW','$'
    MENU_HINT9      DB '9.QUIT','$'
    NUMBER_HINT     DB 'PLEASE CHOOSE A NUMBER TO FUNCTION','$'
    USERNAME_HINT   DB 'PLEASE ENTER YOUR USERNAME', '$'
    PASSWORD_HINT   DB  'PLEASE ENTER YOUR PASSWORD', '$'
    SUCCESS_HINT    DB 'AUTH SUCCESS', '$'
    QUERY_HINT      DB 'PLEASE ENTER THE ITEM NAME YOU WANT TO QUERY','$'
    FAIL_HINT       DB 'ACCESS DENIED','$'
    IN_ITEM         DB 80,0,80 DUP(0)
    TEMP            DB 0,0,0,0,'$'
    BUF             DB 10,0,10 DUP(0)
    ADDRESS_TEMP    DW 0


DATA ENDS

CODE SEGMENT  USE16 PARA PUBLIC 'B1'
	ASSUME CS:CODE,DS:DATA,SS:STACK
    START:
               MOV AX,DATA
               MOV DS,AX
               CALL VIEW_ID
VIEW_ID PROC  
               CALL NEWLINE
               MOV AL,AUTH
               CMP AL,0
               JZ N1
               JMP N2
N1:            CALL NEWLINE
               LEA DX,VIEWER_HINT2
               MOV AH,9
               INT 21H
               JMP GOOD_ID
N2:            CALL NEWLINE
               LEA DX,VIEWER_HINT1
               MOV AH,9
               INT 21H
               CALL GOOD_ID
VIEW_ID ENDP
GOOD_ID PROC
               CALL NEWLINE
               MOV AX,GOOD
               CMP AX,0
               JZ MENU
               CMP AX,1
               JZ GO1
               CMP AX,2
               JZ GO2
               CMP AX,3
               JZ GO3
GO1:            CALL NEWLINE
                LEA DX,GOOD_HINT1
                MOV AH,9
                INT 21H
                JMP MENU
GO2:            CALL NEWLINE
                LEA DX,GOOD_HINT2
                MOV AH,9
                INT 21H
                JMP MENU
GO3:            CALL NEWLINE
                LEA DX,GOOD_HINT3
                MOV AH,9
                INT 21H
                JMP MENU
MENU:           CALL NEWLINE
                LEA DX,NUMBER_HINT
                MOV AH,9
                INT 21H
                CALL NEWLINE
                LEA DX,MENU_HINT1
                MOV AH,9
                INT 21H
                CALL NEWLINE
                LEA DX,MENU_HINT2
                MOV AH,9
                INT 21H
                CALL NEWLINE
                LEA DX,MENU_HINT3
                MOV AH,9
                INT 21H
                CALL NEWLINE
                LEA DX,MENU_HINT4
                MOV AH,9
                INT 21H
                CALL NEWLINE
                LEA DX,MENU_HINT5
                MOV AH,9
                INT 21H
                CALL NEWLINE
                LEA DX,MENU_HINT6
                MOV AH,9
                INT 21H
                CALL NEWLINE
                LEA DX,MENU_HINT7
                MOV AH,9
                INT 21H
                CALL NEWLINE
                LEA DX,MENU_HINT8
                MOV AH,9
                INT 21H
                CALL NEWLINE
                LEA DX,MENU_HINT9
                MOV AH,9
                INT 21H
                CALL NEWLINE
                MOV AH,1
                INT 21H
                CMP AL,'1'
                JZ FUNC1D
                CMP AL,'2'
                JZ FUNC2D
                CMP AL,'3'
                JZ FUNC3D
                CMP AL,'4'
                JZ FUNC4D
                CMP AL,'6'
                JZ FUNC6D
                CMP AL,'9'
                JZ FUNC9
                JMP AUTH_FAIL
FUNC1D:         CALL FUNC1
                JMP VIEW_ID
FUNC2D:         CALL FUNC2
                JMP VIEW_ID
FUNC3D:         CALL FUNC3
                JMP VIEW_ID
FUNC4D:         CALL FUNC4
                JMP VIEW_ID
FUNC6D:         CALL FUNC6_PRE
                JMP VIEW_ID
GOOD_ID ENDP

FUNC1 PROC 
        CALL NEWLINE
        LEA DX,SNAME
        MOV AH,9
        INT 21H
        CALL NEWLINE
        LEA DX,USERNAME_HINT
        MOV AH,9
        INT 21H
        CALL NEWLINE
        LEA DX,IN_NAME
        MOV AH,10
        INT 21H
        CALL NEWLINE
        LEA DX,PASSWORD_HINT
        MOV AH,9
        INT 21H
        CALL NEWLINE
        LEA DX,IN_PWD
        MOV AH,10
        INT 21H
        CALL NEWLINE
        MOV SI,OFFSET IN_NAME
        CMP BYTE PTR 2[SI],13
        JZ VIEW_ID
        JMP CHECK_USERNAME

CHECK_USERNAME:
        MOV SI,OFFSET IN_NAME
        MOV EDI,OFFSET BNAME
        MOV BX,0
        JMP LOOPA
LOOPA:  
         MOV AH,BYTE PTR 2[BX+SI]
         MOV AL,BYTE PTR [BX+DI]
         CMP AL,0
         JZ  CHECK_PASSWORD
         CMP AH,AL
         JNZ AUTH_FAILD
         INC BX
         JMP LOOPA
CHECK_PASSWORD:
         MOV SI,OFFSET IN_PWD
         MOV EDI,OFFSET BPASS
         MOV BX,0
         JMP LOOPB
LOOPB:
         MOV BYTE PTR AH,2[BX+SI]
         MOV BYTE PTR AL,[BX+DI]
         CMP AL,0
         JZ AUTH_SUCCESSD
         CMP AH,AL
         JNZ AUTH_FAILD
         INC BX
         JMP LOOPB
         
FUNC1 ENDP
AUTH_FAILD: CALL AUTH_FAIL
            RET
AUTH_SUCCESSD: CALL AUTH_SUCCESS
            RET
AUTH_FAIL1D: CALL AUTH_FAIL1
            RET
AUTH_SUCCESS1D: CALL AUTH_SUCCESS1
            RET
FUNC2 PROC
         CALL NEWLINE
         LEA DX, QUERY_HINT
         MOV AH,9
         INT 21H
         CALL NEWLINE
         LEA DX,IN_ITEM
         MOV AH,10
         INT 21H
         JMP SERCH1
SERCH1:
         MOV SI,OFFSET IN_ITEM
         MOV DI,OFFSET GA1
         MOV BX,0
         JMP LOOPC
LOOPC:   MOV AH,BYTE PTR 2[BX+SI]
         MOV AL,BYTE PTR [BX+DI]
         CMP AH,AL
         JNZ SERCH2
         INC BX
         MOV AH,BYTE PTR 2[BX+SI]
         CMP AH,'#'
         JNZ LOOPC
         MOV GOOD,1
         CALL NEWLINE
         LEA DX,SUCCESS_HINT
         MOV AH,9
         INT 21H
         CALL NEWLINE
         LEA DX,GA1
         MOV AH,9
         INT 21H
         CALL NEWLINE
         CALL PRINT_VALUE
         RET
SERCH2:
         MOV SI,OFFSET IN_ITEM
         MOV DI,OFFSET GA2
         MOV BX,0
         JMP X
X:       MOV AH,BYTE PTR 2[BX+SI]
         MOV AL,BYTE PTR [BX+DI]
         CMP AH,AL
         JNZ SERCH3
         INC BX
         MOV AH,BYTE PTR 2[BX+SI]
         CMP AH,'#'
         JNZ X
         MOV GOOD,2
         LEA DX,SUCCESS_HINT
         MOV AH,9
         INT 21H
         CALL NEWLINE
         LEA DX,GA2
         MOV AH,9
         INT 21H
         CALL NEWLINE
         CALL PRINT_VALUE
         RET
SERCH3:  
         MOV SI,OFFSET IN_ITEM
         MOV DI,OFFSET GA3
         MOV BX,0
         JMP Y
Y:       MOV AH,BYTE PTR 2[BX+SI]
         MOV AL,BYTE PTR [BX+DI]
         CMP AH,AL
         JNZ AUTH_FAIL1D
         INC BX
         MOV AH,BYTE PTR 2[BX+SI]
         CMP AH,'#'
         JNZ Y
         MOV GOOD,3
         LEA DX,SUCCESS_HINT
         MOV AH,9
         INT 21H
         CALL NEWLINE
         LEA DX,GA3
         MOV AH,9
         INT 21H
         CALL NEWLINE
         CALL PRINT_VALUE
         RET
         
FUNC2 ENDP

FUNC3 PROC
         MOV AX,GOOD
         CMP AX,0
         JZ AUTH_FAIL
         MOV AX,0
         CALL TIMER
         CALCULATOR GA1
         CALCULATOR GA2
         MOV SI,OFFSET GAN
         MOV BX,0
         MOV CX,27
         JMP NC
NC:      
         MOV AX,124
         MOV WORD PTR 19[SI+BX],AX
         ADD BX,20
         DEC CX
         CMP CX,0
         JNZ NC
         JMP CALCULATE
         
CALCULATE:
         MOV BX,OFFSET GA3 
         ADD BX,10
         MOV CX,5[BX]
         MOV DX,7[BX]
         SUB CX,DX
         CMP CX,0
         JZ AUTH_FAIL1D
         MOV AX,1
         ADD 7[BX],AX
         MOV AX, WORD PTR 3[BX]
         MOV DL, BYTE PTR [BX]
         MOV DH, 0
         MUL DX
         MOV CX, 10
         DIV CX
         MOV CX,AX
         MOV AX, 1[BX]
         MOV DX,128
         MUL DX
         MOV DX,0
         DIV CX
         MOV CX, AX
         MOV AX, WORD PTR 7[BX]
         MOV DX,64
         MUL DX
         MOV DX,0
         DIV WORD PTR 5[BX]
         ADD AX, CX
         MOV WORD PTR 9[BX],AX
         
         CMP WORD PTR 7[BX],M
         JL CALCULATE
         CALL NEWLINE
          MOV AX,1
         CALL TIMER
         RET
         
FUNC3 ENDP

FUNC4 PROC   
         CALCULATOR GA1
         CALL NEWLINE
         MOV DL,BYTE PTR 9[DI]
         MOV AH,2
         INT 21H
         CALL NEWLINE
         CALCULATOR GA2
         CALL NEWLINE
         MOV DL,BYTE PTR 9[DI]
         MOV AH,2
         INT 21H
         CALL NEWLINE
         CALCULATOR GA3
         CALL NEWLINE
         MOV DL,BYTE PTR 9[DI]
         MOV AH,2
         INT 21H
         CALL NEWLINE
         RET
FUNC4 ENDP
FUNC6_PRE PROC
      CMP AUTH,1
      JNZ FAIL_ACCESS
      CMP GOOD,0
      JZ  FAIL_ACCESS
      CMP GOOD,1
      JZ GA1_VALUE
      CMP GOOD,2
      JZ GA2_VALUE
      CMP GOOD,3
      JZ GA3_VALUE
GA1_VALUE:
         MOV DI,OFFSET GA1
         MOV ADDRESS_TEMP,DI
         CALL NEWLINE
         MOV AL,BYTE PTR 10[DI]
         MOV AH,0
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 11[DI]
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 13[DI]
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 15[DI]
         CALL F2T10
         CALL NEWLINE
         CALL FUNC6
         RET
GA2_VALUE:
         MOV DI,OFFSET GA2
         MOV ADDRESS_TEMP,DI
         CALL NEWLINE
         MOV AL,BYTE PTR 10[DI]
         MOV AH,0
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 11[DI]
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 13[DI]
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 15[DI]
         CALL F2T10
         CALL NEWLINE
         CALL FUNC6
         RET
GA3_VALUE:
         MOV DI,OFFSET GA3
         MOV ADDRESS_TEMP,DI
         CALL NEWLINE
         MOV AL,BYTE PTR 10[DI]
         MOV AH,0
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 11[DI]
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 13[DI]
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 15[DI]
         CALL F2T10
         CALL NEWLINE
         CALL FUNC6
         RET
FAIL_ACCESS:
      LEA DX,FAIL_HINT
      MOV AH,9
      INT 21H
      RET

FUNC6_PRE ENDP
FUNC9 PROC   
         MOV BX,OFFSET GA1
         MOV DL,19[BX]
         MOV AH,2
         INT 21H
         MOV AH,4CH
         INT 21H
         RET
FUNC9 ENDP


AUTH_FAIL PROC
        CALL NEWLINE
        MOV AUTH,0
        LEA DX,FAIL_HINT
        MOV AH,9
        INT 21H
        CALL NEWLINE
        
        RET
AUTH_FAIL ENDP

AUTH_SUCCESS PROC
        CALL NEWLINE
        MOV AUTH,1
        LEA DX,SUCCESS_HINT
        MOV AH,9
        INT 21H
        RET
AUTH_SUCCESS ENDP

AUTH_FAIL1 PROC
        CALL NEWLINE
        
        LEA DX,FAIL_HINT
        MOV AH,9
        INT 21H
        CALL NEWLINE
        
        RET
AUTH_FAIL1 ENDP

AUTH_SUCCESS1 PROC
        CALL NEWLINE
        
        LEA DX,SUCCESS_HINT
        MOV AH,9
        INT 21H
        RET
AUTH_SUCCESS1 ENDP

NEWLINE PROC FAR

    MOV     DL, 13
    MOV     AH, 2H
    INT     21H
    MOV     DL, 10
    MOV     AH, 2H
    INT     21H
    RET
NEWLINE ENDP

TIMER	PROC
	PUSH  DX
	PUSH  CX
	PUSH  BX
	MOV   BX, AX
	MOV   AH, 2CH
	INT 21H	     ;CH=HOUR(0-23),CL=MINUTE(0-59),DH=SECOND(0-59),DL=CENTISECOND(0-100)
	MOV   AL, DH
	MOV   AH, 0
	IMUL  AX,AX,1000
	MOV   DH, 0
	IMUL  DX,DX,10
	ADD   AX, DX
	CMP   BX, 0
	JNZ   _T1
	MOV   CS:_TS, AX
_T0:	POP   BX
	POP   CX
	POP   DX
	RET
_T1:	SUB   AX, CS:_TS
	JNC   _T2
	ADD   AX, 60000
_T2:	MOV   CX, 0
	MOV   BX, 10
_T3:	MOV   DX, 0
	DIV   BX
	PUSH  DX
	INC   CX
	CMP   AX, 0
	JNZ   _T3
	MOV   BX, 0
_T4:	POP   AX
	ADD   AL, '0'
	MOV   CS:_TMSG[BX], AL
	INC   BX
	LOOP  _T4
	PUSH  DS
	MOV   CS:_TMSG[BX+0], 0AH
	MOV   CS:_TMSG[BX+1], 0DH
	MOV   CS:_TMSG[BX+2], '$'
	LEA   DX, _TS+2
	PUSH  CS
	POP   DS
	MOV   AH, 9
	INT   21H
	POP   DS
	JMP   _T0
_TS	DW    ?
 	DB    'TIME ELAPSED IN MS IS '
_TMSG	DB    12 DUP(0)
TIMER   ENDP

RADIX PROC
      PUSH CX
      PUSH EDX
      XOR CX,CX
LOP1: XOR EDX,EDX
      DIV EBX
      PUSH DX
      INC CX
      OR EAX,EAX
      JNZ LOP1
LOP2: POP AX
      CMP AL,10
      JB L1
      ADD AL,7
L1:   ADD AL,30H
      MOV [SI],AL
      INC SI
      LOOP LOP2
      POP EDX
      POP CX
      RET
RADIX ENDP
F2T10 PROC FAR
         PUSH EBX
         PUSH SI
         LEA SI,BUF
         MOVSX EAX,AX
PLUS:    MOV EBX,10
         CALL RADIX
         MOV BYTE PTR [SI],'$'
         LEA DX,BUF
         MOV AH,9
         INT 21H
         POP SI
         POP EBX
         RET
F2T10 ENDP
PRINT_VALUE PROC FAR
         MOV AL,BYTE PTR 10[DI]
         MOV AH,0
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 11[DI]
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 13[DI]
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 15[DI]
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 17[DI]
         CALL F2T10
         CALL NEWLINE
         MOV AX,WORD PTR 19[DI]
         CALL F2T10
         RET
PRINT_VALUE ENDP



CODE     ENDS
      END START