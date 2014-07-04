package com.jsaiyan.test;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

public class TestActivity extends Activity {

	private com.jsaiyan.Unsafe unsafe;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_test);
		
		unsafe = com.jsaiyan.Unsafe.instance();
		
		bypassConstructorTest();
		callSuperTest();
		exceptionTest();
		magicCastTest();
		overrideFinalTest();
	}
	
	
	
	class Animal {
		Animal() {
			Log.e("JSaiyan", "Animal Constructor");
		}
	}
	class Dog extends Animal {
		Dog() {
			Log.e("JSaiyan", "Dog Constructor");
		}
	}
	
	protected void bypassConstructorTest()
	{
		Log.i("JSaiyan", "bypassConstructorTest");
		Dog dog = (Dog)unsafe.allocateObject(Dog.class);
	}
	
	
	class Ninja {
		private void say(String str)
		{
			Log.i("JSaiyan", "This is a private method. Ninja!! " + str);
		}
	}
	
	class MyNinja extends Ninja {
		
		void say(String str)
		{
			Log.i("JSaiyan", "about to call Ninja private super method with jsaiyan");
			try {
				unsafe.callSuperMethod(this, Ninja.class, "say", str);
			} catch (NoSuchMethodException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	
	protected void callSuperTest()
	{
		Log.i("JSaiyan", "callSuperTest");
		Ninja ninja = new MyNinja();
		ninja.say("Hello");
	}
	
	class ChuckNorris {
		public void kick() {
			unsafe.throwException(new Exception("ChuckNorrisException"));
		}
	}
	
	protected void exceptionTest() {
		Log.i("JSaiyan", "exceptionTest");
		ChuckNorris chuck = new ChuckNorris();
		try {
			chuck.kick();
		}
		catch (Exception ex) {
			Log.i("JSaiyan", "Catched not declared checked Exception with jsaiyan");
		}
		
	}
	
	protected void magicCastTest() {
		Log.i("JSaiyan", "magicCastTest");
		
        Integer integer = new Integer(0);
        unsafe.changeClass(integer, String.class);
        String fakeString = (String)(Object)integer;
        
        Log.i("JSaiyan", "Succeeded casting int to string with jsayan ;)");
	}
	
	
	final class Secure {
		final void say()
		{
			Log.e("JSaiyan", "I feel secure!");
		}
	}
	
	class Attack {
		void say()
		{
			Log.i("JSaiyan", "Overrided final method like a boss with jsaiyan!");
		}
	}
	
	protected void overrideFinalTest()
	{
		Log.i("JSaiyan", "overrideFinalTest");
		
		Attack attack = new Attack();
	    unsafe.changeSuperClass(Attack.class, Secure.class);
	    Secure secure = (Secure)(Object) attack;
	    secure.say();
	}
}
