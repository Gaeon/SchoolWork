package ifexample;

public class IfExample2 {

	public static void main(String[] args) {

		int age = 3;
		int charge;
		if(age > 19)
		{
			System.out.println("성인입니다");
			charge = 10000;
		}
		else if(age > 13)
		{
			System.out.println("중고등학생입니다");
			charge = 5000;
		}
		else if(age > 7)
		{
			System.out.println("초등학생입니다");
			charge = 2500;
		}
		else
		{
			System.out.println("미취학아동입니다");
			charge = 0;
		}
		System.out.println("입장료는 "+charge+"원 입니다.");

	}

}
