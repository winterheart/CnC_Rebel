/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

public class RenegadeNet extends Thread
{
	private String[] _logins = null;
	private double[] _scores = null;
	private RenegadeNetCaller _caller = null;
	
	static 
	{
        System.loadLibrary("RenegadeGR");
    }

	
	private static native int _nativeSendGR(String[] logins, double[] scores);
	public static native void startWinSock();
	public static native void stopWinSock();
	
	
	public RenegadeNet(RenegadeNetCaller caller)
	{
		_caller = caller;
	}
	
	
	public void sendGameResults(String[] logins, double[] scores)
	{
		_logins = logins;
		_scores = scores;
		start();
		/*RenegadeNet thread = new RenegadeNet();		
		thread.setRequest(caller, logins, scores);
		thread.run();*/
	}	
	
	/*public void setRequest(RenegadeNetCaller caller, String[] logins, double[] scores)
	{
		_caller = caller;
		_logins = logins;
		_scores = scores;
	}*/	
	
	public void run()
	{
		int packetlen = _nativeSendGR(_logins, _scores);
		_caller.grDoneCallback(packetlen);
	}    
}
