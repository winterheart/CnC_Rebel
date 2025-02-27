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

//RenegadeSim.java
import com.ms.wfc.app.*;
import com.ms.wfc.core.*;
import com.ms.wfc.ui.*;
import java.util.*;

/**
 * @author: Application Wizard
 * @version: 1.0
 * This class can take a variable number of parameters on the command
 * line. Program execution begins with the main() method. The class
 * constructor is not invoked unless an object of type 'RenegadeSim'
 * created in the main() method.
 */ 

public class RenegadeSim extends Form implements RenegadeNetCaller
{
	private Date _seed = new Date();
	private Random _rand = new Random(_seed.getSeconds());
		
		
	public void doNew(Object sender, Event e)
	{
		// New
	}

	private void saveAsMenu_click(Object sender, Event e)
	{
		// Save As
	}

	private void saveMenu_click(Object sender, Event e)
	{
		// Save
	}

	private void doOpen(Object sender, Event e)
	{
		// Open
	}

	public void wordWrapMenu_click(Object sender, Event e)
	{
		// WordWrap 
	}

	public void doDateTime(Object sender, Event e)
	{
		// Date/Time
	}

	public void doPaste(Object sender, Event e)
	{
		// Paste
		try 
		{	
		}
		catch (Exception ecx)
		{
		}
	}

	public void doCopy(Object sender, Event e)
	{
		// Copy
	}

	public void doCut(Object sender, Event e)
	{
		// Cut
	}

	public void exitMenu_click(Object sender, Event e)
	{
		// Exit		
			Application.exit();
	}

	private void aboutMenu_click(Object sender, Event e)
	{
		About myAbout = new About();
		myAbout.showDialog ();
	}

	private void toolBar_buttonClick(Object source, ToolBarButtonClickEvent e)
	{
		if (e.button == openToolBarButton) {	
			// Open
			doOpen(source,e);
		}
		else if (e.button == saveToolBarButton) {	
			// Save
			doSave(source,e);
		}
		else if (e.button == setupToolBarButton) {	
			// Setup
			ClientSetup myClientSetup = new ClientSetup();
			myClientSetup.showDialog();
		}
		else  {	
			; //nop
		}
}

	public RenegadeSim()
	{
			super();

		//Required for Visual J++ Form Designer support
		initForm();		

		//TODO: Add any constructor code after initForm call
		RenegadeNet.startWinSock();
		_refreshButtonStates();
		Application.addOnIdle(new EventHandler(this.RenegadeSim_Idle));
	}


	/**
	 * RenegadeSim overrides dispose so it can clean up the
	 * component list.
	 */
	public void dispose()
	{
		super.dispose();
		components.dispose();
		RenegadeNet.stopWinSock();
	}

	private void RenegadeSim_Idle(Object sender, Event e)
	{
		// Set the statusBarStates
		/*StatusBarPanel sbPanel[] = statusBar.getPanels ();
		if ((GetKeyState(VK_CAPITAL) & 1) == 1)
			sbPanel[1].setText ("CAP");		
		else		
			sbPanel[1].setText ("");		
		if ((GetKeyState(VK_NUMLOCK) & 1) == 1)
			sbPanel[2].setText ("NUM");		
		else	
			sbPanel[2].setText ("");		*/
	}
	
	private boolean doSave(Object sender, Event e)
	{
		boolean bRc = false;
		return bRc;
	}


	private void RenegadeSim_click(Object source, Event e)
	{
		
	}

	private void label1_click(Object source, Event e)
	{
		
	}
	
	private void butSimulate_click(Object source, Event e)
	{
		int[] indices = lbPlayers.getSelectedIndices();
		int i = 0;
		
		lbResults.removeAll();
		for(i = 0; i < lbPlayers.getItemCount(); i++)
			lbResults.addItem(new String("--"));
		
		for(i = 0; i < indices.length; i++)
		{
			// Simulate a score.  We want a score x such that -0.5 <= x <= 0.5
			// and we want to weight it slightly more towards the positive side.
			double score = _rand.nextDouble() - 0.3;
			if( score > 0.5 ) score = 0.5;
			if( score < -0.5 ) score = -0.5;
			lbResults.setItem(indices[i], new String("" + (_rand.nextDouble() - 0.5)));
		}
		
		_refreshButtonStates();
	}

	private void butSelectToggle_click(Object source, Event e)
	{
		int[] indices = lbPlayers.getSelectedIndices();
		for(int i = 0; i < lbPlayers.getItemCount(); i++)
			lbPlayers.setSelected(i, (indices.length == 0));
		_refreshButtonStates();
	}
	
	
	private void _refreshButtonStates()
	{
		boolean valid = false;
		
		// Check for Send button
		for(int i = 0; i < lbResults.getItemCount(); i++)
		{
			String item = (String)lbResults.getItem(i);
			if( item.compareTo("--") != 0 )
				valid = true;
		}
		butSend.setEnabled(valid);
		
		
		// Check for simulate button
		int[] indices = lbPlayers.getSelectedIndices();
		butSimulate.setEnabled(indices.length > 0);
	}

	private void lbPlayers_selectedIndexChanged(Object source, Event e)
	{
		_refreshButtonStates();
	}

	private void butSend_click(Object source, Event e)
	{
		int[] indices = lbPlayers.getSelectedIndices();		
		String logins[] = new String[indices.length];
		double scores[] = new double[indices.length];
		Double tmpDouble = null;
		
		
		for(int i = 0; i < indices.length; i++)
		{
			logins[i] = new String((String)lbPlayers.getItem(indices[i]));
			try
			{
				tmpDouble = new Double((String)lbResults.getItem(indices[i]));
			}
			catch( NumberFormatException exp )
			{
				/* TODO:  Error dialog... */
			}
			scores[i] = tmpDouble.doubleValue();
		}
		
		
		_setStatusMessage("Connecting to games2.westwood.com:4608...");
		RenegadeNet net = new RenegadeNet(this);
		net.sendGameResults(logins, scores);		
	}
	
	
	public void grDoneCallback(int packetlen)
	{
		if( packetlen <= 0 )
			_setStatusMessage("ERROR: " + packetlen + " (The server may be down)");
		else
			_setStatusMessage("Sent " + packetlen + " bytes to server successfully.");
	}
	
	
	private void _setStatusMessage(String s)
	{
		(statusBar.getPanels())[0].setText(s);
	}								  

	private void setupMenu_click(Object source, Event e)
	{
		ClientSetup myClientSetup = new ClientSetup();
		myClientSetup.showDialog();
	}
	

	/**
	 * NOTE: The following code is required by the Visual J++ form
	 * designer.  It can be modified using the form editor.  Do not
	 * modify it using the code editor.
	 */

	Container components = new Container();
	MainMenu mainMenu1 = new MainMenu();
	MenuItem fileMenu = new MenuItem();
	MenuItem openMenu = new MenuItem();
	MenuItem saveMenu = new MenuItem();
	MenuItem seperator3Menu = new MenuItem();
	MenuItem exitMenu = new MenuItem();
	Label label1 = new Label();
	MenuItem helpMenu = new MenuItem();
	MenuItem aboutMenu = new MenuItem();
	MenuItem saveAsMenu = new MenuItem();
	StatusBar statusBar = new StatusBar();
	StatusBarPanel mainStatusBarPanel = new StatusBarPanel();
	ListBox lbResults = new ListBox();
	ToolBar toolBar = new ToolBar();
	ToolBarButton openToolBarButton = new ToolBarButton();
	ToolBarButton saveToolBarButton = new ToolBarButton();
	ToolBarButton toolBarButton1 = new ToolBarButton();
	ImageList toolBarImageList = new ImageList();
	Label label2 = new Label();
	Button butSend = new Button();
	Button butSimulate = new Button();
	ListBox lbPlayers = new ListBox();
	GroupBox groupBox1 = new GroupBox();
	Button butSelectToggle = new Button();
	MenuItem setupMenu = new MenuItem();
	MenuItem menuItem1 = new MenuItem();
	ToolBarButton setupToolBarButton = new ToolBarButton();

	private void initForm()
	{
		// NOTE:  This form is storing resource information in an
		// external file.  Do not modify the string parameter to any
		// resources.getObject() function call. For example, do not
		// modify "foo1_location" in the following line of code
		// even if the name of the Foo object changes: 
		//   foo1.setLocation((Point)resources.getObject("foo1_location"));

		IResourceManager resources = new ResourceManager(this, "RenegadeSim");
		openMenu.setShortcut(Shortcut.CTRL_O);
		openMenu.setText("&Open Results...");
		openMenu.addOnClick(new EventHandler(this.doOpen));

		saveMenu.setShortcut(Shortcut.CTRL_S);
		saveMenu.setText("&Save Results...");
		saveMenu.addOnClick(new EventHandler(this.saveMenu_click));

		seperator3Menu.setText("-");

		exitMenu.setText("E&xit");
		exitMenu.addOnClick(new EventHandler(this.exitMenu_click));

		label1.setLocation(new Point(16, 16));
		label1.setSize(new Point(72, 16));
		label1.setTabIndex(2);
		label1.setTabStop(false);
		label1.setText("Players:");
		label1.addOnClick(new EventHandler(this.label1_click));

		aboutMenu.setText("&About...");
		aboutMenu.addOnClick(new EventHandler(this.aboutMenu_click));

		helpMenu.setMenuItems(new MenuItem[] {
							  aboutMenu});
		helpMenu.setText("&Help");

		saveAsMenu.setText("Save &As...");
		saveAsMenu.addOnClick(new EventHandler(this.saveAsMenu_click));

		mainStatusBarPanel.setAutoSize(StatusBarPanelAutoSize.SPRING);
		mainStatusBarPanel.setWidth(256);

		statusBar.setBackColor(Color.CONTROL);
		statusBar.setLocation(new Point(0, 289));
		statusBar.setSize(new Point(272, 20));
		statusBar.setTabIndex(1);
		statusBar.setText("");
		statusBar.setShowPanels(true);
		statusBar.setPanels(new StatusBarPanel[] {
							mainStatusBarPanel});

		lbResults.setLocation(new Point(120, 32));
		lbResults.setSize(new Point(128, 147));
		lbResults.setTabIndex(1);
		lbResults.setText("listBox1");
		lbResults.setUseTabStops(true);
		lbResults.setItems(new Object[] {
						   "--", 
						   "--", 
						   "--", 
						   "--", 
						   "--", 
						   "--", 
						   "--", 
						   "--", 
						   "--", 
						   "--"});

		openToolBarButton.setImageIndex(1);
		openToolBarButton.setToolTipText("Open Results");

		saveToolBarButton.setImageIndex(2);
		saveToolBarButton.setToolTipText("Save Results");

		toolBarButton1.setStyle(ToolBarButtonStyle.SEPARATOR);
		toolBarButton1.setText("toolBarButton4");

		toolBarImageList.setImageSize(new Point(16, 15));
		toolBarImageList.setImageStream((ImageListStreamer)resources.getObject("toolBarImageList_imageStream"));
		/* @designTimeOnly toolBarImageList.setLocation(new Point(176, 8)); */

		label2.setLocation(new Point(120, 16));
		label2.setSize(new Point(48, 16));
		label2.setTabIndex(3);
		label2.setTabStop(false);
		label2.setText("Results:");

		butSend.setLocation(new Point(184, 256));
		butSend.setSize(new Point(80, 23));
		butSend.setTabIndex(3);
		butSend.setText("Send Results");
		butSend.addOnClick(new EventHandler(this.butSend_click));

		butSimulate.setLocation(new Point(128, 216));
		butSimulate.setSize(new Point(128, 16));
		butSimulate.setTabIndex(2);
		butSimulate.setText("Simulate Game Results");
		butSimulate.addOnClick(new EventHandler(this.butSimulate_click));

		lbPlayers.setLocation(new Point(16, 32));
		lbPlayers.setSize(new Point(88, 147));
		lbPlayers.setTabIndex(0);
		lbPlayers.setText("listBox1");
		lbPlayers.setSelectionMode(SelectionMode.MULTI_SIMPLE);
		lbPlayers.setUseTabStops(true);
		lbPlayers.setItems(new Object[] {
						   "test1", 
						   "test5", 
						   "test7", 
						   "test8", 
						   "test9", 
						   "test13", 
						   "test14", 
						   "test16", 
						   "noxstinky", 
						   "goodmach"});
		lbPlayers.addOnSelectedIndexChanged(new EventHandler(this.lbPlayers_selectedIndexChanged));

		groupBox1.setLocation(new Point(8, 32));
		groupBox1.setSize(new Point(256, 216));
		groupBox1.setTabIndex(6);
		groupBox1.setTabStop(false);
		groupBox1.setText("Renegade Game Simulator");

		butSelectToggle.setLocation(new Point(16, 184));
		butSelectToggle.setSize(new Point(88, 16));
		butSelectToggle.setTabIndex(4);
		butSelectToggle.setText("Select All / None");
		butSelectToggle.addOnClick(new EventHandler(this.butSelectToggle_click));

		setupMenu.setText("&Client Setup");
		setupMenu.addOnClick(new EventHandler(this.setupMenu_click));

		menuItem1.setText("-");

		fileMenu.setMenuItems(new MenuItem[] {
							  openMenu, 
							  saveMenu, 
							  saveAsMenu, 
							  seperator3Menu, 
							  setupMenu, 
							  menuItem1, 
							  exitMenu});
		fileMenu.setText("&File");

		mainMenu1.setMenuItems(new MenuItem[] {
							   fileMenu, 
							   helpMenu});
		/* @designTimeOnly mainMenu1.setLocation(new Point(80, 8)); */

		this.setAnchor(ControlAnchor.ALL);
		this.setLocation(new Point(298, 88));
		this.setText("Renegade Simulator Applet");
		this.setAutoScaleBaseSize(new Point(5, 13));
		this.setBorderStyle(FormBorderStyle.FIXED_TOOLWINDOW);
		this.setClientSize(new Point(272, 309));
		this.setMaximizeBox(false);
		this.setMenu(mainMenu1);
		this.addOnClick(new EventHandler(this.RenegadeSim_click));

		setupToolBarButton.setImageIndex(4);
		setupToolBarButton.setToolTipText("Client Setup");

		toolBar.setSize(new Point(272, 25));
		toolBar.setTabIndex(0);
		toolBar.setButtons(new ToolBarButton[] {
						   openToolBarButton, 
						   saveToolBarButton, 
						   toolBarButton1, 
						   setupToolBarButton});
		toolBar.setDropDownArrows(true);
		toolBar.setImageList(toolBarImageList);
		toolBar.setShowToolTips(true);
		toolBar.addOnButtonClick(new ToolBarButtonClickEventHandler(this.toolBar_buttonClick));

		this.setNewControls(new Control[] {
							butSimulate, 
							butSend, 
							groupBox1, 
							toolBar, 
							statusBar});
		groupBox1.setNewControls(new Control[] {
								 butSelectToggle, 
								 label2, 
								 label1, 
								 lbResults, 
								 lbPlayers});
	}

	/**
	 * The main entry point for the application. 
	 *
	 * @param args Array of parameters passed to the application
	 * via the command line.
	 */
	public static void main(String args[])
	{
		Application.run(new RenegadeSim());
	}

	public static final int VK_CAPITAL = 0x14;
	public static final int VK_NUMLOCK = 0x90;
	/**
	 * @dll.import("USER32",auto) 
	 */
	public static native short GetKeyState(int nVirtKey);
}
