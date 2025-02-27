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

import com.ms.wfc.app.*;
import com.ms.wfc.core.*;
import com.ms.wfc.ui.*;
import com.ms.wfc.html.*;

/**
 * This class can take a variable number of parameters on the command
 * line. Program execution begins with the main() method. The class
 * constructor is not invoked unless an object of type 'ClientSetup'
 * created in the main() method.
 */
public class ClientSetup extends Form
{
	public ClientSetup()
	{
		super();

		// Required for Visual J++ Form Designer support
		initForm();		

		// TODO: Add any constructor code after initForm call
	}

	/**
	 * ClientSetup overrides dispose so it can clean up the
	 * component list.
	 */
	public void dispose()
	{
		super.dispose();
		components.dispose();
	}

	private void okButton_click(Object source, Event e)
	{
		this.setDialogResult(DialogResult.OK);
	}

	/**
	 * NOTE: The following code is required by the Visual J++ form
	 * designer.  It can be modified using the form editor.  Do not
	 * modify it using the code editor.
	 */
	Container components = new Container();
	Button okButton = new Button();
	GroupBox groupBox1 = new GroupBox();
	Label label1 = new Label();
	Edit edit1 = new Edit();
	Label label2 = new Label();
	Edit edit2 = new Edit();

	private void initForm()
	{
		this.setText("Client Setup");
		this.setAutoScaleBaseSize(new Point(5, 13));
		this.setClientSize(new Point(247, 135));

		okButton.setLocation(new Point(168, 104));
		okButton.setSize(new Point(75, 23));
		okButton.setTabIndex(0);
		okButton.setText("Ok");
		okButton.addOnClick(new EventHandler(this.okButton_click));

		groupBox1.setLocation(new Point(8, 8));
		groupBox1.setSize(new Point(232, 88));
		groupBox1.setTabIndex(1);
		groupBox1.setTabStop(false);
		groupBox1.setText("Game Results Server");

		label1.setLocation(new Point(8, 24));
		label1.setSize(new Point(32, 16));
		label1.setTabIndex(0);
		label1.setTabStop(false);
		label1.setText("Host:");

		edit1.setLocation(new Point(40, 24));
		edit1.setSize(new Point(184, 20));
		edit1.setTabIndex(2);
		edit1.setText("games2.westwood.com");

		label2.setLocation(new Point(8, 56));
		label2.setSize(new Point(32, 16));
		label2.setTabIndex(3);
		label2.setTabStop(false);
		label2.setText("Port:");

		edit2.setLocation(new Point(40, 56));
		edit2.setSize(new Point(40, 20));
		edit2.setTabIndex(1);
		edit2.setText("4850");

		this.setNewControls(new Control[] {
							groupBox1, 
							okButton});
		groupBox1.setNewControls(new Control[] {
								 edit2, 
								 label2, 
								 edit1, 
								 label1});
	}

	/**
	 * The main entry point for the application. 
	 *
	 * @param args Array of parameters passed to the application
	 * via the command line.
	 */
	public static void main(String args[])
	{
		Application.run(new ClientSetup());
	}
}
