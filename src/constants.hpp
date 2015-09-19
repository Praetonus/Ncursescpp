#ifndef NCURSESCPP_CONSTANTS_HPP_
#define NCURSESCPP_CONSTANTS_HPP_

namespace nccpp
{

namespace attributes
{

extern int const normal;
extern int const standout;
extern int const underline;
extern int const reverse;
extern int const blink;
extern int const dim;
extern int const bold;
extern int const protect;
extern int const invis;
extern int const altcharset;
extern int const chartext;

} // namespace attributes

namespace internal
{

struct DefaultColor
{
	operator short const() const;
};

} // namespace internal

namespace colors
{

extern internal::DefaultColor const def;
extern short const black;
extern short const red;
extern short const green;
extern short const yellow;
extern short const blue;
extern short const magenta;
extern short const cyan;
extern short const white;

} // namespace colors

namespace internal
{

struct FunctionKeys
{
	int operator()(int) const;
};

}

namespace keys
{

extern int const break_k;
extern int const sreset;
extern int const reset;
extern int const down;
extern int const up;
extern int const left;
extern int const right;
extern int const home;
extern int const backspace;
extern internal::FunctionKeys const f;
extern int const dl;
extern int const il;
extern int const dc;
extern int const ic;
extern int const eic;
extern int const clear;
extern int const eos;
extern int const eol;
extern int const sf;
extern int const sr;
extern int const npage;
extern int const ppage;
extern int const stab;
extern int const ctab;
extern int const catab;
extern int const enter;
extern int const print;
extern int const ll;
extern int const a1;
extern int const a3;
extern int const b2;
extern int const c1;
extern int const c3;
extern int const btab;
extern int const beg;
extern int const cancel;
extern int const close;
extern int const command;
extern int const copy;
extern int const create;
extern int const end;
extern int const exit;
extern int const find;
extern int const help;
extern int const mark;
extern int const message;
extern int const move;
extern int const next;
extern int const open;
extern int const options;
extern int const previous;
extern int const redo;
extern int const reference;
extern int const refresh;
extern int const replace;
extern int const restart;
extern int const resume;
extern int const save;
extern int const sbeg;
extern int const scancel;
extern int const scommand;
extern int const scopy;
extern int const screate;
extern int const sdc;
extern int const sdl;
extern int const select;
extern int const send;
extern int const seol;
extern int const sexit;
extern int const sfind;
extern int const shelp;
extern int const shome;
extern int const sic;
extern int const sleft;
extern int const smessage;
extern int const smove;
extern int const snext;
extern int const soptions;
extern int const sprevious;
extern int const sprint;
extern int const sredo;
extern int const sreplace;
extern int const sright;
extern int const srsume;
extern int const ssave;
extern int const ssuspend;
extern int const sundo;
extern int const suspend;
extern int const undo;
extern int const mouse;
extern int const resize;
extern int const event;

} // namespace keys

} // namespace nccpp

#endif // Header guard
