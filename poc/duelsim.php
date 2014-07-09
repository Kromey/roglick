<?php

class Roll
{
	private $die;

	private $num;
	private $mod;

	private $skill;

	public function __construct($n=3, $m=0)
	{
		$this->num = $n;
		$this->mod = $m;

		$this->skill = null;

		$this->die = array();
		for($i = 0; $i < $n; $i++)
		{
			$this->die[] = mt_rand(1, 6);
		}
	}

	public function set_skill($skill)
	{
		$this->skill = $skill;
	}

	public function get_rollmsg()
	{
		return "Rolled {$this->num}d+{$this->mod} and got ".implode(', ', $this->die)." for ".$this->get_result();
	}

	public function get_rolls()
	{
		return $this->die;
	}

	public function get_result()
	{
		return array_sum($this->die) + $this->mod;
	}

	public function get_degreeofsuccess()
	{
		if($this->test_skill())
		{
			return $this->skill - $this->get_result();
		} else {
			return null;
		}
	}

	public function test_skill()
	{
		if(is_null($this->skill))
		{
			return null;
		}
		//echo "Testing skill of {$this->skill} ";

		return $this->skill > $this->get_result();
	}
}

class Character
{
	private $max_str;
	private $max_dex;
	private $max_int;
	private $max_per;

	private $cur_str;
	private $cur_dex;
	private $cur_int;
	private $cur_per;

	private $weap_skill;

	private $ap;

	public function __construct($str, $dex, $int, $per, $weap_skill)
	{
		$this->max_str = $str;
		$this->max_dex = $dex;
		$this->max_int = $int;
		$this->max_per = $per;

		$this->cur_str = $str;
		$this->cur_dex = $dex;
		$this->cur_int = $int;
		$this->cur_per = $per;

		$this->weap_skill = $weap_skill;

		$this->ap = 0;
	}

	public function get_attrs()
	{
		return array(
			$this->cur_str,
			$this->cur_dex,
			$this->cur_int,
			$this->cur_per
		);
	}

	public function get_speed()
	{
		return $this->cur_dex/2 + $this->cur_str/4 + $this->cur_per/4;
	}

	public function get_dodge()
	{
		return $this->get_speed();
	}

	public function tick()
	{
		$this->ap += $this->get_speed();
		return $this->ap > 0;
	}

	public function take_step()
	{
		$this->ap -= 110 - $this->get_speed();
	}

	public function take_swing($weap_weight, $dmg_mod = 0)
	{
		$this->ap -= 100 + 100 * $weap_weight * $weap_weight / $this->cur_str - $this->get_speed();

		$skill_modifier = 0.5 + 0.5 * ($this->cur_str / $this->max_str);
		$skill = $this->weap_skill * $skill_modifier;

		$roll = new Roll();
		$roll->set_skill($skill);
		$result = $roll->test_skill();
		if($result)
		{
			$eff_str = $this->cur_str + floor($roll->get_degreeofsuccess() / 3);
			if($eff_str >= 9)
			{
				$n = floor( ($eff_str - 9)/4 ) + 1;
				$m = ($eff_str - 9)%4 - 1;
			} else {
				$n = 1;
				$m = 6 - floor( $eff_str/2 );
			}

			$dmg = new Roll($n, $m+$dmg_mod);
			return max(1, $dmg->get_result());
		} else {
			return 0;
		}
	}

	public function defend()
	{
		$roll = new Roll();
		$roll->set_skill($this->get_speed());
		return $roll->test_skill();
	}

	public function take_damage($dmg)
	{
		$split = mt_rand() / mt_getrandmax();
		$str_dmg = floor($split * $dmg);
		$dex_dmg = floor((1-$split) * $dmg);

		$this->cur_str -= $str_dmg;
		$this->cur_dex -= $dex_dmg;

		//echo "{$dmg} points of damage split between {$str_dmg} and {$dex_dmg} ";
	}

	public function is_alive()
	{
		return
			$this->cur_str > 0 &&
			$this->cur_dex > 0 &&
			$this->cur_int > 0 &&
			$this->cur_per > 0;
	}
}

$MAX_DUELS = 500;
$stats = array();
$firstbloodvictor = 0;
for($duel = 0; $duel < $MAX_DUELS; $duel++)
{
	$distance = 0;
	$hero = new Character(10, 12, 10, 10, 13);
	$kobold = new Character(13, 10, 10, 10, 13);
	$actors = array(
		array("name"=>"Hero", "char"=>$hero, "weapon"=>array(2,2)),
		array("name"=>"Kobold", "char"=>$kobold, "weapon"=>array(1,1))
	);
	$fight_stats = array(
		"Duel"=>$duel+1,
		"Ticks"=>0,
		"First Blood"=>null,
		"Victor"=>null,
		"Hero Hits"=>0,
		"Hero Dodges"=>0,
		"Kobold Hits"=>0,
		"Kobold Dodges"=>0
	);

	while($distance > 0)
	{
		$fight_stats["Ticks"]++;
		$stepped = false;
		foreach($actors as $actor)
		{
			if($actor['char']->tick())
			{
				$distance--;
				$stepped = true;
				$actor['char']->take_step();
				//echo "{$actor['name']} takes a step! ";
			}
		}

		if($stepped)
		{
			//echo "\n";
		}
	}

	$both_alive = true;
	$dmg = 0;
	$blood_drawn = false;
	while($both_alive)
	{
		$fight_stats["Ticks"]++;
		foreach($actors as $actor)
		{
			if($dmg > 0)
			{
				if($actor['char']->defend())
				{
					//echo "{$actor['name']} dodges the attack!\n";
					$fight_stats["{$actor['name']} Dodges"]++;
				} else {
					$actor['char']->take_damage($dmg);
					if(!$blood_drawn)
					{
						$blood_drawn = true;
						$fight_stats["First Blood"] = $lastactor;
					}
					//echo "{$actor['name']} is reduced to [".implode(', ', $actor['char']->get_attrs())."]\n";

					if(!($both_alive = $actor['char']->is_alive()))
					{
						//echo "\n{$actor['name']} succumbs to his wounds!\n";
						$fight_stats["Victor"] = $lastactor;
						if($fight_stats["First Blood"] == $fight_stats["Victor"])
						{
							$firstbloodvictor++;
						}
					}
				}

				$dmg = 0;
			}

			if(!$both_alive)
			{
				break;
			}

			if($actor['char']->tick())
			{
				$lastactor = $actor['name'];
				//echo "{$actor['name']} takes a swing! ";
				$dmg = $actor['char']->take_swing($actor['weapon'][0], $actor['weapon'][1]);
				if($dmg > 0)
				{
					//echo "It's a hit! ";
					$fight_stats["{$actor['name']} Hits"]++;
				} else {
					//echo "It's a miss! ";
				}
				//echo "\n";
			}
		}
	}

	$stats[] = $fight_stats;
	//echo "\n";
}

//Now we'll print out the stats
echo implode(',', array_keys($stats[0]))."\n";
foreach($stats as $stat)
{
	echo implode(',', $stat)."\n";
}
echo "First Blood Is Victor,{$firstbloodvictor},".round(100*$firstbloodvictor/$MAX_DUELS, 2)."%\n";

