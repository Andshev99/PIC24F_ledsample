/*
    LED sample
*/

/*
 PIC24F MCU Peripheral Library 
 MPLAB C �̃C���X�g�[���t�H���_���� Microchip PIC24F Peripheral Library.chm �Q��
*/
#define USE_AND_OR 
#include<ports.h>
#include<timer.h>
#include<PwrMgnt.h>

/* �R���t�B�O���[�V���� */
 _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
 _CONFIG2(POSCMOD_HS & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
 _CONFIG3(WPFP_WPFP0 & SOSCSEL_IO & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
 _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)

unsigned short output = 0;

/* �^�C�}�[���荞�� */
void __attribute__ ((interrupt,no_auto_psv)) _T2Interrupt(void)
{
	if(output == 0)
	{
		output |= IOPORT_BIT_15; /* �|�[�g��1�� */
	}else{
		output &= ~IOPORT_BIT_15; /* �|�[�g��0�� */
	}
	/* PORT�o�� RB15 */
	mPORTBWrite(output);
	/* �^�C�}�[���荞�݃N���A */
	T2_Clear_Intr_Status_Bit;
}

int main ( void )
{
	/* �S�Ă�A/D�ϊ��|�[�g��I/O�Ɏg�p�ł���悤�ɐݒ� */
	AD1PCFG = 0xffff;
	/* �N���b�N��PLL prescaler (1:1)�Ŏg�p���� */
    CLKDIV = 0x0000;

	/* PORTB RB15���o�͂ɐݒ� */
	mPORTBOutputConfig(IOPORT_BIT_15);

	/* PORTB��0���o�� */
	mPORTBWrite(0);

	/* �^�C�}�[���荞�݂�L���� */
	ConfigIntTimer2(T2_INT_ON|T2_INT_PRIOR_1);
	/* �^�C�}�[��ݒ� */
	OpenTimer2(T2_ON | T2_PS_1_64 ,0x9000);

	/* ���C�����[�v */
    while (1)
    {
		/* IDLE���[�h�Ɉڍs */
		mPWRMGNT_GotoIdleMode();
	}
}
