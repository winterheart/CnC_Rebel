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

// About.java
import com.ms.wfc.app.*;
import com.ms.wfc.core.*;
import com.ms.wfc.ui.*;

/**
 * @author: Application Wizard
 * @version: 1.0
 * This class can take a variable number of parameters on the command
 * line. Program execution begins with the main() method. The class
 * constructor is not invoked unless an object of type '%FILENAME%'
 * created in the main() method.
*/
public class About extends Form
{
	private void okButton_click(Object sender, Event e)
	{
		this.setDialogResult(DialogResult.OK);
	}

	public About()
	{
		super();

		//Required for Visual J++ Form Designer support
		initForm();		
		
		// Set Avail System Memory Information
		com.ms.win32.MEMORYSTATUS lpMemStat = new com.ms.win32.MEMORYSTATUS();
		GlobalMemoryStatus(lpMemStat);
		availableMemoryLabel.setText(Integer.toString(lpMemStat.dwTotalPhys/1024) + " KB");

	}

	/**
	 * %FILENAME% overrides dispose so it can clean up the
	 * component list.
	 */
	public void dispose()
	{
		super.dispose();
		components.dispose();
	}

	/**
	 * NOTE: The following code is required by the Visual J++ form
	 * designer.  It can be modified using the form editor.  Do not
	 * modify it using the code editor.
	 */

	Container components = new Container();
	Button okButton = new Button();
	Label titleLabel = new Label();
	Label versionLabel = new Label();
	Label nameLabel = new Label();
	Label memoryLabel = new Label();
	Label availableMemoryLabel = new Label();

	private void initForm()
	{
		okButton.setLocation(new Point(208, 192));
		okButton.setSize(new Point(84, 23));
		okButton.setTabIndex(0);
		okButton.setText("OK");
		okButton.addOnClick(new EventHandler(this.okButton_click));

		this.setText("RenegadeSim");
		this.setAcceptButton(okButton);
		this.setAutoScaleBaseSize(new Point(5, 13));
		this.setBorderStyle(FormBorderStyle.FIXED_TOOLWINDOW);
		this.setCancelButton(okButton);
		this.setClientSize(new Point(298, 241));
		this.setMaximizeBox(false);
		this.setMinimizeBox(false);
		this.setStartPosition(FormStartPosition.CENTER_SCREEN);

		titleLabel.setFont(new Font("MS Sans Serif", 15.0f, FontSize.CHARACTERHEIGHT, FontWeight.BOLD, false, false, false));
		titleLabel.setLocation(new Point(10, 10));
		titleLabel.setSize(new Point(280, 40));
		titleLabel.setTabIndex(1);
		titleLabel.setTabStop(false);
		titleLabel.setText("Renegade Game Results Simulator");

		versionLabel.setLocation(new Point(10, 60));
		versionLabel.setSize(new Point(280, 20));
		versionLabel.setTabIndex(3);
		versionLabel.setTabStop(false);
		versionLabel.setText("Version 0.1a");

		nameLabel.setLocation(new Point(10, 90));
		nameLabel.setSize(new Point(280, 50));
		nameLabel.setTabIndex(4);
		nameLabel.setTabStop(false);
		nameLabel.setText("Randomly computes a set of scores given a bunch of Renegade players and calls a C++ DLL via JNI to deliver game results packets to the Renegade game results server.");

		memoryLabel.setLocation(new Point(8, 160));
		memoryLabel.setSize(new Point(200, 24));
		memoryLabel.setTabIndex(2);
		memoryLabel.setTabStop(false);
		memoryLabel.setText("Memory available to system: ");

		availableMemoryLabel.setLocation(new Point(212, 160));
		availableMemoryLabel.setSize(new Point(72, 24));
		availableMemoryLabel.setTabIndex(5);
		availableMemoryLabel.setTabStop(false);
		availableMemoryLabel.setText("");

		this.setNewControls(new Control[] {
							nameLabel, 
							versionLabel, 
							titleLabel, 
							memoryLabel, 
							availableMemoryLabel, 
							okButton});
	}

	/**
	 * The main entry point for the application. 
	 *
	 * @param args Array of parameters passed to the application
	 * via the command line.
	 */
	public static void main(String args[])
	{
		Application.run(new About());
	}

	/**
	 * @dll.import("KERNEL32",auto) 
	 */
	public static native void GlobalMemoryStatus(com.ms.win32.MEMORYSTATUS lpBuffer);
}
