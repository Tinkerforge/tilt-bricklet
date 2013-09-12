program ExampleSimple;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletTilt;

type
  TExample = class
  private
    ipcon: TIPConnection;
    al: TBrickletTilt;
  public
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change to your UID }

var
  e: TExample;

procedure TExample.Execute;
var tiltState: byte;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  al := TBrickletTilt.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Get current tilt state }
  tiltState := al.GetTiltState;

  case tiltState of
    BRICKLET_TILT_TILT_STATE_CLOSED:
    begin
      WriteLn('closed');
    end;
    BRICKLET_TILT_TILT_STATE_OPEN:
	begin
      WriteLn('open');
    end;
    BRICKLET_TILT_TILT_STATE_CLOSED_VIBRATING:
	begin
      WriteLn('closed vibrating');
    end;
  end;

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
