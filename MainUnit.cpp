//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
class Fraction
{
	private:
	int num;
	int denom;

	public:
	explicit Fraction(int num = 1, int denom = 1): num(num), denom(denom) {}
	~Fraction(){}

	void SetDenom(int d) {denom = d; if (denom == 0)denom = 1;}
	void SetNum(int n) {num = n;}

	int GetDenom() {return denom;}
	int GetNum() {return num;}

	void PrintFrac(TEdit * NumEdit, TEdit * DenomEdit) {
		NumEdit->Text = num;
		DenomEdit->Text = denom;
	}

	void ReadFrac(TEdit * NumEdit, TEdit * DenomEdit) {
		num = NumEdit->Text.ToInt();
		denom = DenomEdit->Text.ToInt();
		if (denom == 0)denom = 1;
	}
	void Rotate(){
		int tmp = denom;
		denom = num;
		num = tmp;
	}

	void Multiply(Fraction * multiplier){
		num *= multiplier->GetNum();
		denom *= multiplier->GetDenom();
	}

	void Divide(Fraction * multiplier){
		denom *= multiplier->GetNum();
		num *= multiplier->GetDenom();
	}

	int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}

	void Reduce()
	{
		int GCD = gcd(num, denom);
		num /= GCD;
		denom /= GCD;
	}

	//a*b/gcd(a, b)
	int lcd(int a, int b){
		return a*b/gcd(a,b);
	}

	void Add(Fraction* Adder)
	{
		int LCD = lcd(denom, Adder->GetDenom());
		num = num*(LCD/denom) + (LCD/Adder->GetDenom())*Adder->GetNum();
		denom = LCD;
	}

	void Subtract(Fraction* Subtr)
	{
		int LCD = lcd(denom, Subtr->GetDenom());
		num = num*(LCD/denom) - (LCD/Subtr->GetDenom())*Subtr->GetNum();
		denom = LCD;
	}


};

Fraction frac1, frac2;

//---------------------------------------------------------------------------
void __fastcall TMainForm::BtnRotateClick(TObject *Sender)
{
	frac1.ReadFrac(EditFrac1Num, EditFrac1Denom);
	frac1.Rotate();
	frac1.PrintFrac(EditFrac1Num, EditFrac1Denom);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnReduceClick(TObject *Sender)
{
	frac1.ReadFrac(EditFrac1Num, EditFrac1Denom);
	frac1.Reduce();
	frac1.PrintFrac(EditFrac1Num, EditFrac1Denom);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnAddClick(TObject *Sender)
{
	frac1.ReadFrac(EditFrac1Num, EditFrac1Denom);
	frac2.ReadFrac(EditFrac2Num, EditFrac2Denom);
	frac1.Reduce();
	frac2.Reduce();
	frac1.Add(&frac2);
	frac1.Reduce();
	frac1.PrintFrac(EditResultNum, EditResultDenom);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnSubtractClick(TObject *Sender)
{
	frac1.ReadFrac(EditFrac1Num, EditFrac1Denom);
	frac2.ReadFrac(EditFrac2Num, EditFrac2Denom);
	frac1.Reduce();
	frac2.Reduce();
	frac1.Subtract(&frac2);
	frac1.Reduce();
	frac1.PrintFrac(EditResultNum, EditResultDenom);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnMultiplyClick(TObject *Sender)
{
	frac1.ReadFrac(EditFrac1Num, EditFrac1Denom);
	frac2.ReadFrac(EditFrac2Num, EditFrac2Denom);
	frac1.Reduce();
	frac2.Reduce();
	frac1.Multiply(&frac2);
	frac1.Reduce();
	frac1.PrintFrac(EditResultNum, EditResultDenom);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnDivideClick(TObject *Sender)
{
	frac1.ReadFrac(EditFrac1Num, EditFrac1Denom);
	frac2.ReadFrac(EditFrac2Num, EditFrac2Denom);
	frac1.Reduce();
	frac2.Reduce();
	frac1.Divide(&frac2);
	frac1.Reduce();
	frac1.PrintFrac(EditResultNum, EditResultDenom);
}
//---------------------------------------------------------------------------

