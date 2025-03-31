<?php

class Complaint {
    private $id;
    private $title;
    private $description;

    public function __construct($title, $description) {
        $this->title = $title;
        $this->description = $description;
    }

    public function getId() {
        return $this->id;
    }

    public function getTitle() {
        return $this->title;
    }

    public function getDescription() {
        return $this->description;
    }

    public function setId($id) {
        $this->id = $id;
    }

    public function save($db) {
        $stmt = $db->prepare("INSERT INTO complaints (title, description) VALUES (?, ?)");
        $stmt->bind_param("ss", $this->title, $this->description);
        $stmt->execute();
        $this->id = $db->insert_id;
        $stmt->close();
    }

    public static function getAllComplaints($db) {
        $result = $db->query("SELECT * FROM complaints");
        return $result->fetch_all(MYSQLI_ASSOC);
    }
}